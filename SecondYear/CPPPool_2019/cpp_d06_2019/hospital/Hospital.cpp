/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Hospital.hpp"

// C++ includes
#include <iostream>

Hospital::Hospital()
    : _doctors { nullptr }
    , _nurses  { nullptr }
    , _koalas  { nullptr }
{
}

Hospital::~Hospital()
{
}

void Hospital::addDoctor(KoalaDoctorList * doctor)
{
    KoalaDoctorList * list = _doctors;

    while (list != nullptr)
    {
        if (doctor == list)
            return;
        list = list->getNext();
    }

    if (!doctor)
        return;
    if (!_doctors)
        _doctors = doctor;
    else
        _doctors->append(doctor);
    std::cout << "[HOSPITAL] Doctor " << doctor->getKoalaName() <<
                 " just arrived!\n";
    doctor->timeCheck();
}

void Hospital::addNurse(KoalaNurseList * nurse)
{
    KoalaNurseList * list = _nurses;

    while (list != nullptr)
    {
        if (nurse == list)
            return;
        list = list->getNext();
    }

    if (!nurse)
        return;
    if (!_nurses)
        _nurses = nurse;
    else
        _nurses->append(nurse);
    std::cout << "[HOSPITAL] Nurse " << nurse->getKoalaID() <<
                 " just arrived!\n";
    nurse->timeCheck();
}

void Hospital::addSick(SickKoalaList * sick)
{
    SickKoalaList * list = _koalas;

    while (list != nullptr)
    {
        if (sick == list)
            return;
        list = list->getNext();
    }

    if (!sick)
        return;
    if (!_koalas)
        _koalas = sick;
    else
        _koalas->append(sick);
    std::cout << "[HOSPITAL] Patient " << sick->getKoalaName() <<
                 " just arrived!\n";
}

void Hospital::rest()
{
    while (_nurses != nullptr)
    {
        _nurses->timeCheck();
        _nurses = _nurses->remove(_nurses);
    }

    while (_doctors != nullptr)
    {
        _doctors->timeCheck();
        _doctors = _doctors->remove(_doctors);
    }

    while (_koalas->getNext() != nullptr)
        _koalas = _koalas->remove(_koalas);
}

void Hospital::work()
{
    KoalaDoctorList * doctor = _doctors;
    KoalaNurseList * nurse   = _nurses;
    SickKoalaList * koala    = _koalas;

    while (koala != nullptr)
    {
        if (!doctor)
            doctor = _doctors;
        if (!nurse)
            nurse = _nurses;

        doctor->diagnose(koala);
        nurse->heal(koala);

        doctor = doctor->getNext();
        nurse = nurse->getNext();
        koala = koala->getNext();
    }

}

void Hospital::run()
{
    if (!_doctors || !_nurses || !_koalas)
        return;
    std::cout << "[HOSPITAL] Work starting with:\n";
    _doctors->dump();
    _nurses->dump();
    _koalas->dump();
    std::cout << std::endl;
    work();
    rest();
}
