/*
** A Kevin Pruvost's project, May 2020
** User.hpp
** File description:
** User
*/

#pragma once

#include "Team.hpp"

class User
{
public:
    User(const std::string & nname = "", const std::string & uuidd = "", bool conn = false);
    ~User();

public:
    std::string name;
    std::string uuid;
    bool connected = false;

public:
    std::string teamId;
    std::string channelId;
    std::string threadId;
};