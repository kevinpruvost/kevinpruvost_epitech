/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** TimeModule
*/

#include "TimeModule.hpp"

TimeModule::TimeModule()
{
}

TimeModule::~TimeModule()
{
}

std::string TimeModule::getDate() const
{
    return this->_date;
}

std::string TimeModule::getHour() const
{
    return this->_hour;
}

bool TimeModule::parsing()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    end = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(end);

    tm local_tm = *localtime(&tt);

    this->_date = std::to_string(local_tm.tm_mday) + '/' + std::to_string(local_tm.tm_mon + 1)
        + '/' + std::to_string(local_tm.tm_year + 1900) ;

    this->_hour = std::to_string(local_tm.tm_hour) + ':' + std::to_string(local_tm.tm_min) + ':'
        + std::to_string(local_tm.tm_sec);
    if (this->_debug == true) {
        std::cout << this->_date << std::endl;
        std::cout << this->_hour << std::endl;
    }
    return true;
}
