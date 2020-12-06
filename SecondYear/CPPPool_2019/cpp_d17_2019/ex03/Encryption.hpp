/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/31
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include "IEncryptionMethod.hpp"

#include <string>

class Encryption
{
public:
    Encryption(IEncryptionMethod & enc, void (IEncryptionMethod::* ptr)(char));

    void operator()(char c);

    static void encryptString(IEncryptionMethod &encryptionMethod,
                              std::string const &toEncrypt);

    static void decryptString(IEncryptionMethod &encryptionMethod,
                              std::string const &toDecrypt);

private:
    void              (IEncryptionMethod::*_func)(char);
    IEncryptionMethod & _enc;
};

#endif // ENCRYPTION_HPP
