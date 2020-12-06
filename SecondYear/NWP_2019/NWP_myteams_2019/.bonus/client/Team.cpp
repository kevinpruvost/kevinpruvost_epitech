/*
** A Kevin Pruvost's project, May 2020
** Team.cpp
** File description:
** team
*/

#include "Team.hpp"

Team::Team(const std::string & id, const std::string & nam, const std::string & description)
    : uuid { id }
    , name { nam }
    , desc { description }
{
}

Team::~Team()
{
}