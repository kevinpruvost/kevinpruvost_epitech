/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** PapaXmasElf
*/

#pragma once

#include "Hand.hpp"
#include "Display.hpp"

enum ObjTypes
{
	GIFT,
	BOX,
	TOY,
	IN,
	OUT,
	STOP
};

class PapaXmasElf : virtual public IElf
{
	public:
		PapaXmasElf();
		~PapaXmasElf();

	Object * take(size_t index, ITable *table) override;
	Object * take(IConveyorBelt * conveyorBelt) override;
    bool put(ITable * table) override;
    bool put(IConveyorBelt * conveyorBelt) override;
	Wrap * pressIn(Button * button) override;
    bool pressOut(Button * button) override;

	bool open(Wrap * wrap) override;
    bool close(Wrap * wrap) override;
    bool isOpened(Wrap * wrap) override;
    Wrap *wrapMeThat(Wrap *wrap) override;

	PapaXmasConveyorBelt *getConveyor();
    ITable *getTable() override;
	void setConveyor(PapaXmasConveyorBelt * conveyor);
    void setTable(ITable * table) override;

	bool isComplete(Object * object);
	bool tableHasToy();
	bool tableHasBox();
	bool tableHasPaperGift();
	bool isToyInBox();
	bool display(std::string to_display = "");

	int toyPosition();

	bool recIsToy(Wrap *wrap);

	ObjTypes actionToDo();

	bool moveConveyorToTable();
	bool packAGift() override;

	std::vector<std::string> look(ITable * table) override;

	protected:
	private:
		Hand _hand;
		PapaXmasConveyorBelt *_conveyor;
};
