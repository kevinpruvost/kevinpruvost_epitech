/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** Hand
*/

#pragma once

#include "IElf.hpp"
#include "PapaXmasConveyorBelt.hpp"

class Hand {
	public:
		Hand(IElf * elf);
		~Hand();

        Wrap * pressIn(Button * button);
        bool pressOut(Button * button);

		Object * take(size_t index, ITable *table);
		Object * take(IConveyorBelt * conveyorBelt);
    	bool put(ITable * table);
    	bool put(IConveyorBelt * conveyorBelt);
		bool objectIsWrap();
		Object *getObject();
		void setObject(Object * object);

	protected:
	private:
        IElf * _elf = nullptr;
		Object * _object = nullptr;
};
