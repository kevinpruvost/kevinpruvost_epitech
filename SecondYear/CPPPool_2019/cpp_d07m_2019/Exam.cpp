/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Exam.hpp"

#include <iostream>

bool Exam::cheat = false;

Exam::Exam(bool * cheat)
    : adress (cheat)
{
}

void Exam::start(int nb)
{
    std::cout << "[The exam is starting]\n";
    std::cout << nb << " Klingon vessels appeared out of nowhere.\n"
              << "they are fully armed and shielded\n";
    if (cheat)
        std::cout << "What the... someone changed the parameters of the exam !\n";
    else
        std::cout << "This exam is hard... you lost again.\n";
}

bool Exam::isCheating()
{
    return *adress;
}
