/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef KOALABOT_HPP
#define KOALABOT_HPP

// Project includes
#include "Parts.hpp"

class KoalaBot
{
public:
    KoalaBot();

    void setParts(const Arms & arms);
    void setParts(const Legs & legs);
    void setParts(const Head & head);

    void swapParts(Arms & arms);
    void swapParts(Legs & legs);
    void swapParts(Head & head);

    void informations();

    bool status();

private:
    Head _head;
    Arms _arms;
    Legs _legs;

    std::string _name;
};

#endif // KOALABOT_HPP
