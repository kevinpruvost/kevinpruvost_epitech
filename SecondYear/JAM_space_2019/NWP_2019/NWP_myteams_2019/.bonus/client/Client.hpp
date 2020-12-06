/*
** A Kevin Pruvost's project, May 2020
** Client.hpp
** File description:
** client
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#include "client.h"
}
#endif

// Project includes
#include "KVector.hpp"
#include "User.hpp"

// C++ includes
#include <string>
#include <thread>
#include <condition_variable>
#include <array>

class Client
{
public:
    Client(int ac, char ** av);
    ~Client();

    int exec();

private:
    int client_part(int ac, char ** av);

    void treatResponse(const std::string & str);

    void eventloggedIn(const KVector<std::string> & tab, const std::string & str);
    void eventloggedOut(const KVector<std::string> & tab, const std::string & str);
    void eventmpReceived(const KVector<std::string> & tab, const std::string & str);
    void eventthreadMsgReceived(const KVector<std::string> & tab, const std::string & str);
    void eventprintUsers(const KVector<std::string> & tab, const std::string & str);
    void eventprintTeams(const KVector<std::string> & tab, const std::string & str);
    void eventprintChannels(const KVector<std::string> & tab, const std::string & str);
    void eventprintThread(const KVector<std::string> & tab, const std::string & str);
    void eventprintReplies(const KVector<std::string> & tab, const std::string & str);
    void eventmpPrintMsg(const KVector<std::string> & tab, const std::string & str);
    void eventunknownTeam(const KVector<std::string> & tab, const std::string & str);
    void eventunknownChannel(const KVector<std::string> & tab, const std::string & str);
    void eventunknownThread(const KVector<std::string> & tab, const std::string & str);
    void eventunknownUser(const KVector<std::string> & tab, const std::string & str);
    void eventunauthorized(const KVector<std::string> & tab, const std::string & str);
    void eventnoEvent(const KVector<std::string> & tab, const std::string & str);

    void addUser(const std::string & name, const std::string & uuid, bool connected = true);
    void disconnectUser(const std::string & name, const std::string & uuid);

    void addTeam(const std::string & name, const std::string & uuid, const std::string & desc);
    void addChannel(const std::string & name, const std::string & uuid, const std::string & desc);
    void addThread(const std::array<std::string, 5> & array);
    void addReplies(const std::array<std::string, 4> & array);

    Team & findTeam(const std::string & uuid);
    Channel & findChannel(const std::string & uuid);
    Thread & findThread(const std::string & uuid);

    int _ac;
    char ** _av;

    std::thread clientThread;
    std::thread readingThread;

public:
    std::string getDisplay();
    void launchCommand(const std::string & command);

private:
    std::string toDisplay;

public:
    User _account;
    KVector<User> _users;
    KVector<Team> _teams;

    std::array<std::string, 3> _usedUuids = {"", "", ""};

    std::condition_variable cond;
    std::condition_variable condConnected;
    bool commandLaunchedWaiting = false;

    bool connected = false;
};