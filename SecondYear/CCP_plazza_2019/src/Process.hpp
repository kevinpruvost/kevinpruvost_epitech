/*
** EPITECH PROJECT, 2020
** Process.hpp
** File description:
** process
*/

#pragma once

// Project includes
#include "Exception.hpp"

// C includes
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>

extern bool workingProcess;
extern bool isChildProcess;

void waitForSignal();
std::string readFromFd(int fd);
void writeToFd(int fd, const std::string & line);
void kills(int pid, size_t times);

#define SEND_KILL_WORKING_PROCESS kills(pid, 0)

#define SEND_CHILD_READY kills(basePid, 1)

#define CHILD_STDOUT_READ  pipeFdsChild[0]
#define CHILD_STDOUT_WRITE pipeFdsChild[1]
#define PARENT_STDOUT_READ  pipeFdsParent[0]
#define PARENT_STDOUT_WRITE pipeFdsParent[1]
#define BUFFER_SIZE 1024

enum Command
{
    GetPizzas,
    GetKitchens,
    AddPizza,
    Exit
};

typedef struct header_t
{
    Command command;
    size_t size;
    void * buffer;
} header_t;

void writeBinaryToFd(int fd, const header_t & header);
header_t * readBinaryFromFd(int fd);

class Process
{
public:
    Process();
    ~Process();

    bool isChild();
    bool isParent();
    void killChildProcess();
    std::string read();
    header_t * readBinary();
    void write(const std::string & line);
    void write(const header_t & header);
    void init();

    int getPid() { return pid; }
    void closeFds();

protected:
    bool inited = false;
    int pid;
    int pipeFdsParent[2];
    int pipeFdsChild[2];
    int basePid;
};

void myExit();