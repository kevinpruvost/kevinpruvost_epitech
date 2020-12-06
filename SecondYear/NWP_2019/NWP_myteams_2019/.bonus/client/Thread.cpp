/*
** A Kevin Pruvost's project, May 2020
** Thread.cpp
** File description:
** thread
*/

#include "Thread.hpp"

Thread::Thread(const std::string & threadid, const std::string & userid,
           const std::string & timee, const std::string & titlee, const std::string & message)
        : uuid { threadid }
        , creatorUuid { userid }
        , time { timee }
        , title { titlee }
        , msg { message }
{
}

Thread::~Thread()
{
}