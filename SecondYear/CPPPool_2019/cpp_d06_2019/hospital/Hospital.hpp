/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

// Project includes
#include "KoalaDoctorList.hpp"
#include "KoalaNurseList.hpp"
#include "SickKoalaList.hpp"

class Hospital
{
public:
    Hospital();
    ~Hospital();

public:
    void addDoctor(KoalaDoctorList * doctor);
    void addNurse(KoalaNurseList * nurse);
    void addSick(SickKoalaList * sick);

    void run();

private:
    void rest();
    void work();

private:
    KoalaDoctorList * _doctors;
    KoalaNurseList *  _nurses;
    SickKoalaList *   _koalas;
};

#endif // HOSPITAL_HPP
