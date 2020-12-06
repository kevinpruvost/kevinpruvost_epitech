/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Event.hpp"

#include <list>
#include <functional>
#include <iostream>

class EventManager
{
public:
    EventManager();
    ~EventManager();
    EventManager(EventManager  const &other);
    EventManager &operator =( EventManager  const &rhs);

public:
    void  addEventList(std::list <Event> &events);
    void  addTime(unsigned  int  time);
    void  dumpEvents ()  const;
    void  dumpEventAt(unsigned  int  time) const;
    void  addEvent(const  Event &e);
    void  removeEventsAt(unsigned  int  time);

public:
    std::list<Event> _events;
    unsigned int _time = 0;
};

#endif // EVENTMANAGER_HPP
