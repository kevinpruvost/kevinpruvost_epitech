/*
** A Kevin Pruvost's project, May 2020
** User.cpp
** File description:
** User
*/

#include "User.hpp"

User::User(const std::string & nname, const std::string & uuidd, bool conn)
    : name { nname }
    , uuid { uuidd }
    , connected { conn }
{
}

User::~User()
{
}