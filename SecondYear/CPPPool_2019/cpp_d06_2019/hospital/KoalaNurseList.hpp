/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef KOALANURSELIST_HPP
#define KOALANURSELIST_HPP

// Project includes
#include "KoalaNurse.hpp"
#include "SickKoalaList.hpp"

class KoalaNurseList
{
public:
    KoalaNurseList(KoalaNurse * koala);
    ~KoalaNurseList();

    bool isEnd();
    void append(KoalaNurseList * list);
    KoalaNurse * getFromID(const int id);
    KoalaNurseList * remove(KoalaNurseList * ptr);
    KoalaNurseList * removeFromID(const int id);
    KoalaNurse * getContent();
    void dump();

public:
    void dumpID();
    KoalaNurseList * getNext();
    int getKoalaID();
    void setNext(KoalaNurseList * ptr);
    void timeCheck();
    std::string readReport(const std::string fileName);
    void heal(SickKoalaList * koala);

private:
    KoalaNurse *     _koala;
    KoalaNurseList * _next;
};

#endif // KOALANURSELIST_HPP
