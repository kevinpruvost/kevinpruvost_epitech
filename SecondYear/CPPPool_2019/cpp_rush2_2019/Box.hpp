/*
** EPITECH PROJECT, 2020
** Box.hpp
** File description:
** Box class declaration
*/

#pragma once

#include "Wrap.hpp"

class Box : public Wrap
{
    public:
        Box();
        ~Box();

    public:
        Wrap * wrapMeThat(Object * object) override;

    private:
        Object *_objectContained;
        bool _opened = true;
};