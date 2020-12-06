/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef DROIDMEMORY_HPP
#define DROIDMEMORY_HPP

// C++ includes
#include <cstddef>
#include <iostream>

class DroidMemory
{
public:
    DroidMemory();
    ~DroidMemory();

public:
    size_t getFingerprint() const ;
    size_t getExp() const ;

    void setFingerprint(size_t fingerprint);
    void setExp(size_t exp);

    DroidMemory & operator<<(const DroidMemory & mem);
    DroidMemory & operator>>(DroidMemory & mem) const;
    DroidMemory & operator+=(const DroidMemory & mem);
    DroidMemory & operator+=(const size_t & mem);
    DroidMemory operator+(const DroidMemory & mem);
    DroidMemory operator+(const size_t & mem);

    bool operator==(const DroidMemory & droid) const;
    bool operator!=(const DroidMemory & droid) const;
    bool operator>(const DroidMemory & droid) const;
    bool operator<(const DroidMemory & droid) const;
    bool operator<=(const DroidMemory & droid) const;
    bool operator>=(const DroidMemory & droid) const;

private:
    size_t Fingerprint;
    size_t Exp;
};

std::ostream & operator<<(std::ostream & os, DroidMemory & droidMem);

#endif // DROIDMEMORY_HPP
