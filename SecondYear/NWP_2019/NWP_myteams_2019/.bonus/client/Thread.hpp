/*
** A Kevin Pruvost's project, May 2020
** thread.hpp
** File description:
** dzdq
*/

#pragma once

#include "Reply.hpp"

class Thread
{
public:
    Thread(const std::string & threadid, const std::string & userid,
           const std::string & timee, const std::string & title, const std::string & message);
    ~Thread();

public:
    KVector<Reply> replies;
    std::string uuid;
    std::string creatorUuid;
    std::string time;
    std::string title;
    std::string msg;
};