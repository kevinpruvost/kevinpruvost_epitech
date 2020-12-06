/*
** A Kevin Pruvost's project, May 2020
** Team.hpp
** File description:
** team
*/

#pragma once

#include "Channel.hpp"

class Team
{
public:
    Team(const std::string & id, const std::string & nam, const std::string & description);
    ~Team();

public:
    KVector<Channel> channels;
    std::string uuid;
    std::string name;
    std::string desc;
};