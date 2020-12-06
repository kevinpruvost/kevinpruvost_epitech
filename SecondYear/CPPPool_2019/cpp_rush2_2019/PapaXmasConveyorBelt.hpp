/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** PapaXmasConveyorBelt
*/

#pragma once

#include "Button.hpp"
#include "GiftPaper.hpp"
#include "Box.hpp"

class PapaXmasConveyorBelt : virtual public IConveyorBelt
{
	public:
		PapaXmasConveyorBelt();
		~PapaXmasConveyorBelt();

	Wrap * in() override;
	bool out() override;
	bool put(Object * object) override;
	Object *take() override;
	Object *get() override;

	Button * getButton();

	Wrap *randomGetConveyor();

protected:
private:
	Button _button;
	bool randID = false;
};
