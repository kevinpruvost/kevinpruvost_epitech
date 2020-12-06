/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** UserModule
*/

#include "UserModule.hpp"

UserModule::UserModule()
{
}

UserModule::~UserModule()
{
}

static std::string getHostName()
{
    struct utsname sysinfo;
    uname(&sysinfo);
    return (sysinfo.nodename);
}

bool UserModule::parsing()
{
    _hostname = getHostName();
    auto user = std::getenv("USER");
    if (user != nullptr)
        _username = user;
    return (true);
}