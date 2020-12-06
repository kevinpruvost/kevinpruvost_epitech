/*
** A Kevin Pruvost's project, May 2020
** channel.cpp
** File description:
** channel
*/

#include "Channel.hpp"

Channel::Channel(const std::string & id, const std::string & nam, const std::string & description)
    : uuid { id }
    , name { nam }
    , desc { description }
{
}

Channel::~Channel()
{
}