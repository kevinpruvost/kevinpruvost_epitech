/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** IElf
*/

#pragma once

//C++ includes
#include "ITable.hpp"
#include "Button.hpp"

class IElf
{
	public:
        virtual Object *take(size_t index, ITable * table) = 0;
        virtual Object *take(IConveyorBelt * conveyorBelt) = 0;
        virtual bool put(ITable * table) = 0;
        virtual bool put(IConveyorBelt * conveyorBelt) = 0;
        virtual Object * pressIn(Button * button) = 0;
        virtual bool pressOut(Button * button) = 0;
        virtual bool open(Wrap * wrap) = 0;
        virtual bool close(Wrap * wrap) = 0;
        virtual bool isOpened(Wrap * wrap) = 0;
        virtual Object *wrapMeThat(Wrap *wrap) = 0;

        virtual std::vector<std::string> look(ITable * table) = 0;

        virtual ITable *getTable() = 0;

        virtual void setTable(ITable * table) = 0;

        virtual bool packAGift() = 0;

    protected:
        Object *_object = nullptr;
        ITable * _table = nullptr;

    private:
};
