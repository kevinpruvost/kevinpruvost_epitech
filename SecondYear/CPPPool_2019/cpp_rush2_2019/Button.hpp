/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** Button
*/

#pragma once

#include "IConveyorBelt.hpp"

class Button : virtual public IButton
{
	public:
		Button(IConveyorBelt * conveyor);
		~Button();

		Wrap * in() override;
		bool out() override;

	private:
		IConveyorBelt *_conveyor;
};
