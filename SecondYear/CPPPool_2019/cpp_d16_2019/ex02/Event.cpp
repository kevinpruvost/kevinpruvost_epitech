/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Event.hpp"

Event::Event()
    : _time { 0 }
    , _event { "" }
{
}

Event::Event(unsigned  int time , const  std:: string &event)
    : _time { time }
    , _event { event }
{
}

Event::~Event()
{

}

Event::Event(const  Event &other)
    : _time { other._time }
    , _event { other._event }
{
}

Event & Event::operator =(const  Event &rhs)
{
    _time = rhs.getTime();
    _event = rhs.getEvent();
    return *this;
}

unsigned  int  Event::getTime () const
{
    return _time;
}

const std::string & Event::getEvent () const
{
    return _event;
}

void           Event::setTime(unsigned  int  time)
{
    _time = time;
}

void           Event::setEvent(const  std:: string &event)
{
    _event = event;
}
