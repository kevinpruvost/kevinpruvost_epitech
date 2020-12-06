/*
** EPITECH PROJECT, 2020
** GiftPaper.hpp
** File description:
** GiftPaper class declaration
*/

#pragma once

//C++ includes
#include "Wrap.hpp"

class GiftPaper : public Wrap
{
public:
    GiftPaper();
    ~GiftPaper();

public:
    Wrap * wrapMeThat(Object * object) override;
};