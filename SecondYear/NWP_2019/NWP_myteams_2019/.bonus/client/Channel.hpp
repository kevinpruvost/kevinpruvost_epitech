/*
** A Kevin Pruvost's project, May 2020
** Channel.hpp
** File description:
** channel
*/

#pragma once

#include "Thread.hpp"

class Channel
{
public:
    Channel(const std::string & id, const std::string & nam, const std::string & description);
    ~Channel();

public:
    KVector<Thread> threads;
    std::string uuid;
    std::string name;
    std::string desc;
};