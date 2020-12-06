/*
** EPITECH PROJECT, 2020
** Wrap.hpp
** File description:
** Wrap class declaration
*/

#pragma once

#include "Object.hpp"

class Wrap : public Object
{

public:
    virtual Wrap * wrapMeThat(Object * object) = 0;
    void openMe();
    void closeMe();

    Object * getContainedObject() const;
    Object * takeContainedObject();

    void isTaken() override;

    bool isOpen() const;

    Wrap * containObject(Object *object);

    Wrap & operator<<(Object * object);

private:
    bool _opened = true;
    Object * _objectContained = nullptr;

protected:
    Wrap(const std::string & name = "Wrap");
};

std::ostream & operator<<(std::ostream & os, Wrap * wrap);