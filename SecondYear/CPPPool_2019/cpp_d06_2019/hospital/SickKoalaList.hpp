/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef SICKKOALALIST_HPP
#define SICKKOALALIST_HPP

// Project includes
#include "SickKoala.hpp"

class SickKoalaList
{
public:
    SickKoalaList(SickKoala * koala);
    ~SickKoalaList();

public:
    bool isEnd();
    void append(SickKoalaList * list);
    SickKoala * getFromName(const std::string name);
    SickKoalaList * remove(SickKoalaList * ptr);
    SickKoalaList * removeFromName(const std::string name);
    SickKoala * getContent();
    void dump();

public:
    void dumpName();
    SickKoalaList * getNext();
    std::string getKoalaName();
    void setNext(SickKoalaList * ptr);

private:
    SickKoala *     _koala;
    SickKoalaList * _next;
};

#endif // SICKKOALALIST_HPP
