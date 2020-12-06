/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** PapaXmasTable
*/

#pragma once

#include "ITable.hpp"

class PapaXmasTable : virtual public ITable
{
	public:
		PapaXmasTable();
		~PapaXmasTable();

        bool put(Object * object) override;
        Object *take(int index) override;
		std::vector<std::string> getTitles() override;
		std::vector<Object *> & getAll() override;

		bool isColapsed() override;
		bool isEmpty() override;

		Object * getBox() override;
		Object * getGiftPaper() override;
		Object * getToy() override;

		size_t getSize() override;

	protected:
	private:
};
