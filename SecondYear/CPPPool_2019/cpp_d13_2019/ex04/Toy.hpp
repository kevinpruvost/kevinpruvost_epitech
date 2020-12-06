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
        ALIEN,
        BUZZ,
        WOODY
    };

public:
    Toy();
    Toy(ToyType type, const std::string & name, const std::string & file);
    Toy(const Toy & toy);
    ~Toy();
    Toy & operator =(const Toy & toy);

public:
    virtual bool speak(const std::string & str);
    ToyType getType() const;
    std::string getName() const;
    std::string getAscii() const;
    void setName(const std::string & name);
    bool setAscii(const std::string & file);

    Toy & operator <<(const std::string & str);

    void setPictureString(const std::string & str);

private:
    ToyType _type;
    std::string _name;
    Picture _picture;
};

std::ostream & operator <<(std::ostream & os, const Toy & toy);

#endif // TOY_HPP
