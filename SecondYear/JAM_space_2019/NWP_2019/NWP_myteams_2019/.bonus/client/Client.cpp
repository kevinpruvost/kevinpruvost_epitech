/*
** A Kevin Pruvost's project, May 2020
** Client.cpp
** File description:
** client
*/

#include "Client.hpp"

#include <map>
#include <iostream>

Client::Client(int ac, char ** av)
    : _ac { ac }
    , _av { av }
    , clientThread(&Client::exec, this)
    , readingThread([&]{
        char * temp = nullptr;
        std::string str;

        while (!stop_the_program(false))
        {
            temp = get_last_reponse(NULL);
            if (temp != NULL && temp[0] != 0) {
                if (!connected)
                {
                    connected = true;
                    condConnected.notify_all();
                }
                str = temp;
                if (!str.empty())
                    treatResponse(str);
                free(temp);
            } else
                if (commandLaunchedWaiting)
                {
                    commandLaunchedWaiting = false;
                    cond.notify_all();
                }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    })
{
}

Client::~Client()
{
    kill(SIGINT, getpid());
    stop_the_program(true);
    clientThread.join();
    readingThread.join();
}

static void signal_handler(int sig)
{
    if (sig == SIGINT) {
        stop_the_program(true);
    }
}

int Client::exec()
{
    signal(SIGINT, signal_handler);
    if (help(_ac, _av, "../src/cli/help_msg", 3) == EXIT_FAILURE)
    {
        stop_the_program(true);
        return EXIT_SUCCESS;
    }
    return client_part(_ac, _av);
}

int Client::client_part(int ac, char ** av)
{
    uint16_t port = atoi(av[2]);
    char * ip = av[1];
    client_socket_t socket;

    if (strcmp(ip, "localhost") == 0)
        ip = const_cast<char *>(std::string("127.0.0.1").c_str());
    socket = create_socket(ip, port);
    if (socket.error)
        return EXIT_FAILURE;
    client_loop(socket.distant_fd);
    close_socket(&socket);
    return EXIT_SUCCESS;
}

void Client::treatResponse(const std::string & strd)
{
    static const std::map<int, void (Client::*)(const KVector<std::string> &, const std::string &)>
    funcs = {
        {EVENT_LOGGEDIN, &Client::eventloggedIn},
        {EVENT_LOGGEDOUT, &Client::eventloggedOut},
        {EVENT_MP_RECEIVED, &Client::eventmpReceived},
        {EVENT_THREAD_MSG_RECEIVED, &Client::eventthreadMsgReceived},
        {EVENT_PRINT_USERS, &Client::eventprintUsers},
        {EVENT_PRINT_TEAMS, &Client::eventprintTeams},
        {EVENT_TEAM_PRINT_CHANNELS, &Client::eventprintChannels},
        {EVENT_CHANNEL_PRINT_THREADS, &Client::eventprintThread},
        {EVENT_THREAD_PRINT_REPLIES, &Client::eventprintReplies},
        {EVENT_MP_PRINT_MSG, &Client::eventmpPrintMsg},
        {EVENT_ERROR_UNKNOWN_TEAM, &Client::eventunknownTeam},
        {EVENT_ERROR_UNKNOWN_CHANNEL, &Client::eventunknownChannel},
        {EVENT_ERROR_UNKNOWN_THREAD, &Client::eventunknownThread},
        {EVENT_ERROR_UNKNOWN_USER, &Client::eventunknownUser},
        {EVENT_ERROR_UNAUTHORIZED, &Client::eventunauthorized},
        {NO_EVENT, &Client::eventnoEvent}
    };

    std::string codeStr = strd.substr(0, strd.find_first_of(' '));
    int code = std::stoi(codeStr);

    std::string str = strd.substr(strd.find_first_of(' ') + 1);
    auto vec = splitString(str, " : ");

    if (code >= EVENT_LOGGEDIN && code <= NO_EVENT)
    {
        toDisplay.clear();
        (this->*funcs.at(code))(vec, str);
        if (commandLaunchedWaiting)
        {
            commandLaunchedWaiting = false;
            cond.notify_all();
        }
    }
}

void Client::addUser(const std::string & name, const std::string & uuid, bool connected)
{
    for (const auto & user : _users)
        if (user.name == name || user.uuid == uuid)
            return;
    _users.emplace_back(name, uuid, connected);
}

void Client::disconnectUser(const std::string & name, const std::string & uuid)
{
    for (auto & user : _users)
    {
        if (user.name == name || user.uuid == uuid)
        {
            user.connected = false;
        }
    }
}

void Client::addTeam(const std::string & name, const std::string & uuid, const std::string & desc)
{
    for (const auto & user : _teams)
        if (user.name == name || user.uuid == uuid)
            return;
    _teams.emplace_back(uuid, name, desc);
}

void Client::addChannel(const std::string & name, const std::string & uuid, const std::string & desc)
{
    try
    {
        auto & usedTeam = findTeam(_usedUuids[0]);

        for (const auto & user : usedTeam.channels)
            if (user.name == name || user.uuid == uuid)
                break;
        usedTeam.channels.emplace_back(uuid, name, desc);
    }
    catch(const std::exception& e) {}
}

void Client::addThread(const std::array<std::string, 5> & array)
{
    try
    {
        auto & usedChannel = findChannel(_usedUuids[1]);

        for (const auto & user : usedChannel.threads)
            if (user.uuid == array[0])
                break;
        usedChannel.threads.emplace_back(array[0], array[1], array[2], array[3], array[4]);
    }
    catch(const std::exception& e) {}
}

void Client::addReplies(const std::array<std::string, 4> & array)
{
    try
    {
        auto & usedThread = findThread(_usedUuids[2]);

        usedThread.replies.emplace_back(array[0], array[1], array[2], array[3]);
    }
    catch(const std::exception& e) {}
}

void Client::eventloggedIn(const KVector<std::string> & tab, const std::string &)
{
    addUser(tab[1], tab[0], true);
    toDisplay = tab[1] + " is now connected to the server !";
}

void Client::eventloggedOut(const KVector<std::string> &, const std::string & str)
{
    toDisplay = str + " has disconnected !";
    disconnectUser(str, "");
}

void Client::eventmpReceived(const KVector<std::string> & tab, const std::string &)
{
    toDisplay = tab[0] + "[" + tab[1] + "] whispers: " + tab[2];
}

void Client::eventthreadMsgReceived(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay = "Thread Message Received :\nTeam " + tab[0] + " [" + tab[3] +
    "]:\n\tThread " + tab[1] + " [" + tab[4] + "]:\n\t\t" + tab[2] + " [" + tab[5]
    + "] said: " + tab[6];
}

void Client::eventprintUsers(const KVector<std::string> & tab, const std::string & str)
{
    for (size_t user = 0; !tab.empty() && user * 3 < tab.size(); ++user)
    {
        addUser(tab[(user * 3) + 1], tab[user * 3], std::stoi(tab[(user * 3) + 2]));
    }
}

void Client::eventprintTeams(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Teams :\n";
    for (size_t user = 0; !tab.empty() && user * 3 < tab.size(); ++user)
    {
        addTeam(tab[(user * 3) + 1], tab[user * 3], tab[(user * 3) + 2]);
        toDisplay += tab[(user * 3) + 1] + " [" + tab[user * 3] + "]: " + tab[(user * 3) + 2] + "\n";
    }
}

void Client::eventprintChannels(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Channels :\n";
    for (size_t user = 0; !tab.empty() && user * 3 < tab.size(); ++user)
    {
        addChannel(tab[(user * 3) + 1], tab[user * 3], tab[(user * 3) + 2]);
        toDisplay += tab[(user * 3) + 1] + " [" + tab[user * 3] + "]: " + tab[(user * 3) + 2] + "\n";
    }
}

void Client::eventprintThread(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Threads :\n";
    for (size_t user = 0; !tab.empty() && user * 5 < tab.size(); ++user)
    {
        addThread({tab[(user * 5)], tab[(user * 5) + 1], tab[(user * 5) + 2], tab[(user * 5) + 3], tab[(user * 5) + 4]});
        toDisplay += tab[(user * 5) + 3] + " [" + tab[user * 5] + "]: " + tab[(user * 5) + 4] + "\n";
    }
}

void Client::eventprintReplies(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Replies :\n";
    for (size_t user = 0; !tab.empty() && user * 4 < tab.size(); ++user)
    {
        addReplies({tab[(user * 4)], tab[(user * 4) + 1], tab[(user * 4) + 2], tab[(user * 4) + 3]});
        toDisplay += "[" + tab[(user * 4) + 1] + "] " + tab[user * 4 + 2] + ": " + tab[(user * 4) + 3] + "\n";
    }
}

void Client::eventmpPrintMsg(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Private Messages :\n";
    for (size_t user = 0; !tab.empty() && user * 4 < tab.size(); ++user)
    {
        toDisplay += "[" + tab[(user * 4) + 2] + "] " + tab[(user * 4)] + " [" + tab[user * 4 + 1] + "]: " + tab[(user * 4) + 3] + "\n";
    }
}

void Client::eventunknownTeam(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Wrong Command : [" + tab[0] + "] Team UUID is unknown.";
}

void Client::eventunknownChannel(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Wrong Command : [" + tab[0] + "] Channel UUID is unknown.";
}

void Client::eventunknownThread(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Wrong Command : [" + tab[0] + "] Thread UUID is unknown.";
}

void Client::eventunknownUser(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Wrong Command : [" + tab[0] + "] User UUID is unknown.";
}

void Client::eventunauthorized(const KVector<std::string> & tab, const std::string & str)
{
    toDisplay += "Unauthorized Command : " + str;
}

void Client::eventnoEvent(const KVector<std::string> &, const std::string & str)
{
    toDisplay = str;
}

Team & Client::findTeam(const std::string & uuid)
{
    for (auto & team : _teams)
        if (team.uuid == uuid)
            return team;
    throw EXCEPTION("Not found");
}

Channel & Client::findChannel(const std::string & uuid)
{
    for (auto & team : _teams)
    {
        for (auto & channel : team.channels)
            if (channel.uuid == uuid)
                return channel;
    }
    throw EXCEPTION("Not found");
}

Thread & Client::findThread(const std::string & uuid)
{
    for (auto & team : _teams)
    {
        for (auto & channel : team.channels)
        {
            for (auto & thread : channel.threads)
                if (thread.uuid == uuid)
                    return thread;
        }
    }
    throw EXCEPTION("Not found");
}

std::string Client::getDisplay()
{
    auto temp = toDisplay;
    toDisplay = "";
    return temp;
}

static std::mutex mutex;

void Client::launchCommand(const std::string & command)
{
    int fd = more_pipe(0);
    int ret = 0;

    std::string comm = command;
    comm += "\n";
    while ((ret = write(fd, comm.c_str(), comm.size())) == -1);
    commandLaunchedWaiting = true;
}