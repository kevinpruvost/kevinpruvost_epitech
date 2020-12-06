/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** PapaXmasConveyorBelt
*/

#pragma once

class IButton
{
	public:
		virtual Wrap * in() = 0;
		virtual bool out() = 0;

};