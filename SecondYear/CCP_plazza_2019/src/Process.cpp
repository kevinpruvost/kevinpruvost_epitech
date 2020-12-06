/*
** EPITECH PROJECT, 2020
** Process.cpp
** File description:
** process
*/

#include "Process.hpp"

// C++ includes
#include <ext/stdio_filebuf.h>
#include <istream>
#include <iostream>
#include <streambuf>
#include <fstream>
#include <chrono>
#include <mutex>
#include <condition_variable>

// C includes
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>

bool workingProcess = true;
bool isChildProcess = false;
static bool childReady = false;

static std::mutex mutex;
static std::condition_variable cond;

void myExit()
{
    workingProcess = false;
}

void kills(int pid, size_t times)
{
    for (size_t i = 0; i < times ; ++i)
    {
        kill(pid, SIGUSR1);
        usleep(1000);
    }
    usleep(1000);
    kill(pid, SIGUSR2);
}

static void signalHandler(int sig)
{
    static size_t count = 0;

    std::unique_lock<std::mutex> lock(mutex);
    cond.notify_all();

    if (sig == SIGINT)
    {
        workingProcess = false;
        return;
    }
    if (sig == SIGUSR1)
    {
        ++count;
        return;
    }
    if (sig == SIGUSR2)
    {
        switch (count)
        {
            case 0:
                workingProcess = false;
                break;
            case 1:
                childReady = true;
                break;
        }
        count = 0;
    }
}

Process::Process()
    : pid { getpid() }
{
}

Process::~Process()
{
    if (!inited)
        return;
    if (isParent())
    {
        int status;
        killChildProcess();
        waitpid(pid, &status, WCONTINUED);
    }
}

void Process::init()
{
    if (pipe(pipeFdsChild) == -1 || pipe(pipeFdsParent) == -1)
        throw EXCEPTION("Error with pipe() function.");

    basePid = getpid();
    pid = fork();

    if (pid == -1)
        throw EXCEPTION("Fork problem.");

    inited = true;

    signal(SIGINT, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    if (isParent() && !isChildProcess)
    {
        childReady = false;
        while (workingProcess && !childReady)
        {
            waitForSignal();
        }
        if (!workingProcess)
            return;
    }
    else if (isChild())
    {
        SEND_CHILD_READY;
        isChildProcess = true;
    }
}

std::string Process::read()
{
    if (!workingProcess)
        return "";
    return readFromFd((isChild()) ? CHILD_STDOUT_READ : PARENT_STDOUT_READ);
}

header_t * Process::readBinary()
{
    if (!workingProcess)
        return nullptr;
    return readBinaryFromFd((isChild()) ? CHILD_STDOUT_READ : PARENT_STDOUT_READ);
}

void Process::write(const std::string & line)
{
    writeToFd((isParent()) ? CHILD_STDOUT_WRITE : PARENT_STDOUT_WRITE, line);
}

void Process::write(const header_t & header)
{
    writeBinaryToFd((isParent()) ? CHILD_STDOUT_WRITE : PARENT_STDOUT_WRITE, header);
}

// SMALL METHODS ---------------------------------------------------------------

bool Process::isChild() { return pid == 0; }

bool Process::isParent() { return !isChild(); }

void Process::killChildProcess()
{
    if (isChildProcess || pid == getpid())
        return;
    SEND_KILL_WORKING_PROCESS;
}

void waitForSignal()
{
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock);
}

std::string readFromFd(int fd)
{
    static int timeout_ms = 500;
    std::string str;
    char buffer[BUFFER_SIZE];
    int ret = BUFFER_SIZE - 1;

    memset(buffer, 0, BUFFER_SIZE);
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;
    if (poll(fds, 1, timeout_ms) > 0)
    {
        while ((ret = read(fd, buffer, BUFFER_SIZE - 1)) == BUFFER_SIZE - 1)
        {
            str += buffer;
            memset(buffer, 0, BUFFER_SIZE);
        }
    }
    return buffer;
}

header_t * readBinaryFromFd(int fd)
{
    header_t * header = (header_t *)malloc(sizeof(header_t));
    size_t readSize = 0;

    memset(header, 0, sizeof(header_t));
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;

    while (readSize < sizeof(header_t))
    {
        if (poll(fds, 1, 500) > 0) {
            int ret = read(fd, (char *)header + readSize, sizeof(header_t) - readSize);
            if (ret <= 0) {
                free(header);
                return nullptr;
            }
            readSize += ret;
        }
    }

    if (header->size == 0)
        return header;
    header->buffer = malloc(header->size);

    readSize = 0;
    while (readSize < header->size)
    {
        if (poll(fds, 1, 500) > 0) {
            int ret = read(fd, (char *)header->buffer + readSize, header->size - readSize);
            if (ret <= 0)
            {
                free(header->buffer);
                free(header);
                return nullptr;
            }
            readSize += ret;
        }
    }
    return header;
}

void writeToFd(int fd, const std::string & line)
{
    write(fd, line.c_str(), line.length());
}

void writeBinaryToFd(int fd, const header_t & header)
{
    header_t head;

    memset(&head, 0, sizeof(header_t));
    head.command = header.command;
    head.size = header.size;
    head.buffer = header.buffer;
    write(fd, &head, sizeof(head));
    if (header.size != 0)
        write(fd, header.buffer, header.size);
}

void Process::closeFds()
{
    close(pipeFdsParent[0]);
    close(pipeFdsParent[1]);
    close(pipeFdsChild[0]);
    close(pipeFdsChild[1]);
}