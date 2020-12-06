/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/31
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef CESAR_HPP
#define CESAR_HPP

#include "IEncryptionMethod.hpp"

class Cesar : virtual public IEncryptionMethod
{
public:
    Cesar();

public:
    void encryptChar(char plainChar) override;
    void decryptChar(char cipherChar) override;

    void reset();

private:
    int _shift = 3;
};

#endif // CESAR_HPP
