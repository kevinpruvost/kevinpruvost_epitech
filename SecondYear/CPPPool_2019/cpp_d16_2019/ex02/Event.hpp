/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

class Event
{
public:
    Event();
    Event(unsigned  int time , const  std:: string &event);
    ~Event();
    Event(const  Event &other);
    Event &operator =(const  Event &rhs);

    unsigned  int  getTime () const;
    const  std:: string &getEvent () const;
    void  setTime(unsigned  int  time);
    void  setEvent(const  std:: string &event);

public:
    unsigned int _time;
    std::string _event;
};

#endif // EVENT_HPP
