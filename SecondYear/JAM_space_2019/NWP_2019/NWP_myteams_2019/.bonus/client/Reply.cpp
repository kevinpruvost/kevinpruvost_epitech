/*
** A Kevin Pruvost's project, May 2020
** Reply.cpp
** File description:
** reply
*/

#include "Reply.hpp"

Reply::Reply(const std::string & threadid, const std::string & userid, const std::string & timee, const std::string & message)
    : threadId { threadid }
    , userId { userid }
    , time { timee }
    , msg { message }
{
}

Reply::~Reply()
{
}