/*
** EPITECH PROJECT, 2020
** GiftPaper.cpp
** File description:
** GiftPaper class declaration
*/

//C++ includes
#include "GiftPaper.hpp"

GiftPaper::GiftPaper()
    : Wrap("GiftPaper")
{
}

GiftPaper::~GiftPaper()
{
}

Wrap * GiftPaper::wrapMeThat(Object * object)
{
    return containObject(object);
}