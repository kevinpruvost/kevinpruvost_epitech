/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Errors.hpp"

NasaError::NasaError(const std::string &message, const std::string &component)
    : _message { message }
    , _component { component }
{
}

const std::string & NasaError::getComponent() const
{
    return _component;
}

MissionCriticalError::MissionCriticalError(const std::string &message,
                                           const std::string &component)
    : NasaError(message, component)
{
}

LifeCriticalError::LifeCriticalError(const std::string &message,
                                           const std::string &component)
    : NasaError(message, component)
{
}

UserError::UserError(const std::string &message,
                                           const std::string &component)
    : NasaError(message, component)
{
}

CommunicationError::CommunicationError(const std::string &message)
    : NasaError(message, "CommunicationDevice")
{
}

const char * NasaError::what() const noexcept
{
    return _message.c_str();
}
