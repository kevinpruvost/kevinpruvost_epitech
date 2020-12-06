/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef VICTIM_HPP
#define VICTIM_HPP

// C++ includes
#include <string>
#include <iostream>

class Victim
{
public:
    Victim(const std::string & name);
    ~Victim();

//protected:
//    Victim();

public:
    void say(const std::string & str) const;

public:
    std::string getName() const;
    virtual void getPolymorphed() const;

    void setName(const std::string & name);

private:
    std::string _name;
};

std::ostream & operator<<(std::ostream & os, const Victim & victim);

#endif // VICTIM_HPP
