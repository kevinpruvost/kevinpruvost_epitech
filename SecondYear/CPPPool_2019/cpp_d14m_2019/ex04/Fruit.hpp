/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef FRUIT_HPP
#define FRUIT_HPP

#include <string>

class Fruit
{
public:
    virtual ~Fruit();
    Fruit(const int vitamins, const std::string & name);

public:
    virtual int getVitamins() const;
    virtual std::string getName() const;

    void setVitamins(const int vitamins);
    void setName(const std::string & name);

protected:
    Fruit();
    int _vitamins;
    std::string _name;
};

#endif // FRUIT_HPP
