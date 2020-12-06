/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/31
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Encryption.hpp"

#include <algorithm>
#include <iostream>
#include <functional>

Encryption::Encryption(IEncryptionMethod & enc, void (IEncryptionMethod::*ptr)(char))
    : _func (ptr)
    , _enc  (enc)
{
}

void Encryption::operator ()(char c)
{
    (_enc.*_func)(c);
}


void Encryption::encryptString(IEncryptionMethod &encryptionMethod,
                                      std::string const &toEncrypt)
{
    encryptionMethod.reset();
    std::for_each(toEncrypt.begin(), toEncrypt.end(), Encryption(encryptionMethod, &IEncryptionMethod::encryptChar));
    std::cout << std::endl;
}

void Encryption::decryptString(IEncryptionMethod &encryptionMethod,
                                      std::string const &toDecrypt)
{
    encryptionMethod.reset();
    std::for_each(toDecrypt.begin(), toDecrypt.end(), Encryption(encryptionMethod, &IEncryptionMethod::decryptChar));
    std::cout << std::endl;
}
