/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef KOALANURSE_HPP
#define KOALANURSE_HPP

// Project includes
#include "SickKoala.hpp"

class KoalaNurse
{
public:
    KoalaNurse(int id);
    ~KoalaNurse();

private:
    int _id;
    bool _isWorking;

private:
    void say(const std::string str);

public:
    void giveDrug(const std::string str, SickKoala * sick);
    std::string readReport(const std::string fileName);
    void timeCheck();

public:
    int getID();
};

#endif // KOALANURSE_HPP
