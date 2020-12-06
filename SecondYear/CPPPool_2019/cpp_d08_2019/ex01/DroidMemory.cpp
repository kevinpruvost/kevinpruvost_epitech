/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "DroidMemory.hpp"

// C++ includes
#include <random>

DroidMemory::DroidMemory()
    : Exp { 0 }
{
    Fingerprint = random();
}

DroidMemory & DroidMemory::operator<<(const DroidMemory & mem)
{
    Exp += mem.getExp();
    Fingerprint ^= mem.getFingerprint();
    return *this;
}

DroidMemory & DroidMemory::operator>>(DroidMemory & mem) const
{
    mem.setExp(Exp + mem.getExp());
    mem.setFingerprint(mem.getFingerprint() ^ Fingerprint);
    return mem;
}

DroidMemory & DroidMemory::operator+=(const DroidMemory & mem)
{
    operator<<(mem);
    return *this;
}

DroidMemory & DroidMemory::operator+=(const size_t & exp)
{
    Exp += exp;
    Fingerprint ^= exp;
    return *this;
}

DroidMemory DroidMemory::operator+(const DroidMemory & mem)
{
    DroidMemory newGuy;
    newGuy.setExp(Exp + mem.getExp());
    newGuy.setFingerprint(Fingerprint ^ mem.getFingerprint());
    return newGuy;
}

DroidMemory DroidMemory::operator+(const size_t & exp)
{
    DroidMemory newGuy;
    newGuy.setExp(Exp + exp);
    newGuy.setFingerprint(Fingerprint ^ exp);
    return newGuy;
}

// Getters and Setters ---------------------------------------------------------

size_t DroidMemory::getExp() const { return Exp; }

size_t DroidMemory::getFingerprint() const { return Fingerprint; }

void DroidMemory::setExp(size_t exp) { Exp = exp; }

void DroidMemory::setFingerprint(size_t fingerprint) { Fingerprint = fingerprint; }

// Stand-alone Operators -------------------------------------------------------

std::ostream & operator<<(std::ostream & os, DroidMemory & droidMem)
{
    os << "DroidMemory \'" << droidMem.getFingerprint() << "\', "
       << droidMem.getExp();
    return os;
}
