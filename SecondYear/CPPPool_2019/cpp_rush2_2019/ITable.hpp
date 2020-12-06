/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** ITable
*/

#pragma once

#include "Object.hpp"

// C++ includes
#include <vector>

class ITable
{
	public:
        virtual bool put(Object * object) = 0;
		virtual Object *take(int index) = 0;
        virtual std::vector<std::string> getTitles() = 0;
		virtual std::vector<Object *> & getAll() = 0;

		virtual bool isColapsed() = 0;
		virtual bool isEmpty() = 0;

		virtual size_t getSize() = 0;

		virtual Object * getBox() = 0;
		virtual Object * getGiftPaper() = 0;
		virtual Object * getToy() = 0;


	protected :
		std::vector<Object *> _contained;
		bool _isColapsed = false;
	private:
};