/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef KOALADOCTORLIST_HPP
#define KOALADOCTORLIST_HPP

// Project includes
#include "KoalaDoctor.hpp"
#include "SickKoalaList.hpp"

class KoalaDoctorList
{
public:
    KoalaDoctorList(KoalaDoctor * koala);
    ~KoalaDoctorList();

public:
    bool isEnd();
    void append(KoalaDoctorList * list);
    KoalaDoctor * getFromName(const std::string name);
    KoalaDoctorList * remove(KoalaDoctorList * ptr);
    KoalaDoctorList * removeFromName(const std::string name);
    KoalaDoctor * getContent();
    void dump();

public:
    void dumpName();
    KoalaDoctorList * getNext();
    std::string getKoalaName();
    void setNext(KoalaDoctorList * ptr);
    void timeCheck();
    void diagnose(SickKoalaList * sick);

private:
    KoalaDoctor *     _koala;
    KoalaDoctorList * _next;
};

#endif // KOALADOCTORLIST_HPP
