/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** IConveyorBelt
*/

#pragma once

#include "Wrap.hpp"
#include "IButton.hpp"

class IConveyorBelt
{
	public:
        virtual Wrap * in() = 0;
        virtual bool out() = 0;
        virtual bool put(Object * object) = 0;
		virtual Object *take() = 0;
        virtual Object *get() = 0;

    protected:
        Object *_object = nullptr;
    private:
};
