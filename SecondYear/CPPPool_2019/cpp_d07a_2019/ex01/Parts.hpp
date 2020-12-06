/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef PARTS_HPP
#define PARTS_HPP

// C++ includes
#include <string>

class Parts;
class Head;
class Arms;
class Legs;

class Parts
{
public:
    Parts(const std::string && name, bool functional);
    Parts(const std::string & name, bool functional);

public:
    bool isFunctionnal();
    std::string serial();
    void informationsTemp(const std::string className);

private:
    std::string _name;
    bool        _functionnal;
};

class Head : public Parts
{
public:
    Head(const std::string & string = "H-01", bool functionnal = true);

public:
    void informations();
};

class Arms : public Parts
{
public:
    Arms(const std::string & string = "A-01", bool functionnal = true);

public:
    void informations();
};

class Legs : public Parts
{
public:
    Legs(const std::string & string = "L-01", bool functionnal = true);

public:
    void informations();
};

#endif // PARTS_HPP
