/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef BF_TRANSLATOR_HPP
#define BF_TRANSLATOR_HPP

#include <string>
#include <fstream>
#include <map>

class BF_Translator
{
public:
    BF_Translator();

    int  translate(const  std:: string &in , const  std:: string &out);
};

#endif // BF_TRANSLATOR_HPP
