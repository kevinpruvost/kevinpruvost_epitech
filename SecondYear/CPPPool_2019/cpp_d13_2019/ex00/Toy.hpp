/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef TOY_HPP
#define TOY_HPP

// Project includes
#include "Picture.hpp"

class Toy
{
public:
    enum ToyType
    {
        BASIC_TOY,
        ALIEN
    };

public:
    Toy();
    Toy(ToyType type, const std::string & name, const std::string & file);

public:
    ToyType getType() const;
    std::string getName() const;
    std::string getAscii() const;
    void setName(const std::string & name);
    bool setAscii(const std::string & file);

private:
    ToyType _type;
    std::string _name;
    Picture _picture;
};

#endif // TOY_HPP
