/*
** A Kevin Pruvost's project, May 2020
** tools.cpp
** File description:
** tools
*/

#include "tools.hpp"

KVector<std::string> splitString(const std::string & str, const std::string & delim)
{
    KVector<std::string> cont;
    std::string temp = str;

    while (!temp.empty()) {
        if (temp.find(" : ") == std::string::npos)
            break;
        cont.emplace_back(temp.substr(0, temp.find(" : ")));
        temp = temp.substr(temp.find(" : ") + 3);
    }
    if (!temp.empty())
        cont.emplace_back(temp);
    return cont;
}