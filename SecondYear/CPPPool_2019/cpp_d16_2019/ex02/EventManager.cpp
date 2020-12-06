/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "EventManager.hpp"

EventManager::EventManager()
{

}

EventManager::~EventManager()
{
}

EventManager::EventManager(EventManager  const &other)
{
    _events = other._events;
    _time = other._time;
}

EventManager & EventManager::operator =(const EventManager & rhs)
{
    _events = rhs._events;
    _time = rhs._time;
    return *this;
}

bool inferiorThan(const Event & ev1, const Event & ev2)
{
    if (ev1.getTime() < ev2.getTime())
        return true;
    return false;
}

void  EventManager::addEventList(std::list<Event> &events)
{
    _events.merge(events, inferiorThan);
    for (auto ite = _events.begin(); ite != _events.end();)
    {
        if ((*ite).getTime() <= _time)
        {
            _events.erase(ite);
            ite = _events.begin();
        }
        else
            ++ite;
    }
    _events.sort(inferiorThan);
}

void  EventManager::addTime(unsigned  int  time)
{
    _time += time;
    for (auto ite = _events.begin(); ite != _events.end();)
    {
        Event & event = *ite;
        if (event.getTime() <= _time)
        {
            std::cout << event.getEvent() << std::endl;
            _events.erase(ite);
            ite = _events.begin();
        }
        else
            ++ite;
    }
}

void  EventManager::dumpEvents ()  const
{
    for (const auto event : _events)
        std::cout << event.getTime() << ": " << event.getEvent() << std::endl;
}

void  EventManager::dumpEventAt(unsigned  int  time) const
{
    for (const auto event : _events)
    {
        if (event.getTime() == time)
            std::cout << event.getTime() << ": " << event.getEvent() << std::endl;
    }
}

void  EventManager::addEvent(const  Event &e)
{
    _events.push_back(e);
    _events.sort(inferiorThan);
}

void EventManager::removeEventsAt(unsigned  int  time)
{
    for (auto ite = _events.begin(); ite != _events.end();)
    {
        Event & event = *ite;
        if (event.getTime() == time)
        {
            _events.erase(ite);
            removeEventsAt(time);
            ite = _events.begin();
        }
        else
            ++ite;
    }
    _events.sort(inferiorThan);
}
