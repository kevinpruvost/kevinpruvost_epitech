/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef SICKKOALA_HPP
#define SICKKOALA_HPP

// C++ includes
#include <string>

class SickKoala
{
private:
    std::string _name;
public:
    SickKoala(std::string name);
    ~SickKoala();

private:
    void say(const std::string str);

public:
    void poke();
    bool takeDrug(std::string string);
    void overDrive(std::string string);

public:
    std::string getName();
};

#endif // SICKKOALA_HPP
