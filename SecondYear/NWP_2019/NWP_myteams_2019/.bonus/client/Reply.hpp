/*
** A Kevin Pruvost's project, May 2020
** reply
** File description:
** reply
*/

#pragma once

#include "tools.hpp"

#include <string>

class Reply
{
public:
    Reply(const std::string & threadid, const std::string & userid, const std::string & timee, const std::string & message);
    ~Reply();

public:
    std::string threadId;
    std::string userId;
    std::string time;
    std::string msg;
};