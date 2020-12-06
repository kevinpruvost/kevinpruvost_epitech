/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/31
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef ONETIME_HPP
#define ONETIME_HPP

#include "IEncryptionMethod.hpp"

#include <string>

class OneTime : virtual public IEncryptionMethod
{
public:
    OneTime(const std::string & key);

public:
    void encryptChar(char plainChar) override;
    void decryptChar(char cipherChar) override;

    void reset();

    void shiftChange();

private:
    std::string _key;
    int _shift;
    size_t _index = 0;
};

#endif // ONETIME_HPP
