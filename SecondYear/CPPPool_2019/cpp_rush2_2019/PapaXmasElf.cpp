/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** PapaXmasElf
*/

#include "PapaXmasElf.hpp"

PapaXmasElf::PapaXmasElf()
    : _hand (this)
{
}

PapaXmasElf::~PapaXmasElf()
{
}

bool PapaXmasElf::display(std::string to_display)
{
    std::cout << "------------------------------------------" << std::endl;
    std::cout << to_display << std::endl
    << "Table : " << _table->getTitles() << std::endl;
    if (_conveyor->get())
        std::cout << "Conveyor : " << _conveyor->get()->getName() << std::endl;
    if (_hand.getObject())
        std::cout << "Hand : " << _hand.getObject()->getName() << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

Object * PapaXmasElf::take(size_t index, ITable *table){
    return _hand.take(index, table);
}

Object * PapaXmasElf::take(IConveyorBelt *conveyorBelt){
    return _hand.take(conveyorBelt);
}

bool PapaXmasElf::put(ITable * table) {
    return _hand.put(table);
}

bool PapaXmasElf::put(IConveyorBelt * conveyorBelt) {
    return _hand.put(conveyorBelt);
}

std::vector<std::string> PapaXmasElf::look(ITable * table)
{
    return table->getTitles();
}

Wrap * PapaXmasElf::pressIn(Button * button) {
    return _hand.pressIn(button);
}

bool PapaXmasElf::pressOut(Button * button) {
    return _hand.pressOut(button);
}

bool PapaXmasElf::open(Wrap * wrap)
{
    wrap->openMe();
    return true;
}

bool PapaXmasElf::close(Wrap * wrap)
{
    wrap->closeMe();
    return true;
}

bool PapaXmasElf::isOpened(Wrap * wrap)
{
    return wrap->isOpen();
}

Wrap * PapaXmasElf::wrapMeThat(Wrap *wrap)
{
    if (!wrap)
        return nullptr;
    const auto objet = wrap->wrapMeThat(_hand.getObject());
    if (objet)
        _hand.setObject(objet);
    return objet;
}

PapaXmasConveyorBelt *PapaXmasElf::getConveyor() {
    return _conveyor;
}

ITable *PapaXmasElf::getTable(){
    return _table;
}

void PapaXmasElf::setConveyor(PapaXmasConveyorBelt * conveyor){
    _conveyor = conveyor;    
}

void PapaXmasElf::setTable(ITable * table){
    _table = table;
}

bool PapaXmasElf::moveConveyorToTable() {
    if (this->take(this->_conveyor)){
        this->put(this->_table);
        return true;
    }
    this->put(this->_table);
    return false;
}

bool PapaXmasElf::isComplete(Object * object)
{
    if (object)
    {
        if (object->getName() == "GiftPaper")
        {
            const auto box = ((Wrap *)(object))->getContainedObject();
            if (box && box->getName() == "Box")
            {
                const auto toy = ((Wrap *)(box))->getContainedObject();
                if (toy && toy->getName() != "Box"
                        && toy->getName() != "GiftPaper")
                    return true;
            }
        }
    }
    return false;
}

ObjTypes PapaXmasElf::actionToDo()
{
    if (!_hand.getObject())
        _hand.setObject(_table->getToy());
    if (_hand.getObject() && _hand.getObject()->getName() != "Box" && _hand.getObject()->getName() != "GiftPaper")
    {
        wrapMeThat((Wrap *)_table->getBox());
    }
    if (_hand.getObject() && _hand.getObject()->getName() == "Box")
    {
        wrapMeThat((Wrap *)_table->getGiftPaper());
    }
    if (isComplete(_hand.getObject()))
    {
        if (!put(_conveyor))
        {
            if (!put(_table))
                return ObjTypes::STOP;
            if (!moveConveyorToTable())
                return ObjTypes::STOP;
            take(_table->getSize() - 2, _table);
            put(_conveyor);
        }
        pressOut(_conveyor->getButton());
    }
    return ObjTypes::IN;
}

bool PapaXmasElf::packAGift()
{
    if (!_table || !_conveyor)
        return false;

    if ((!_table->isColapsed() && !_table->isEmpty() && tableHasToy() || _hand.getObject()))
        const auto order = actionToDo();
    display();
    return true;
}

bool PapaXmasElf::tableHasToy() {
    std::vector<std::string> temp = this->_table->getTitles();

    for (const auto part : temp) {
        if (part != "Box" && part != "GiftPaper")
            return true;
    }
    const auto temp2 = _table->getAll();
    for (const auto part : temp2) {
        if (recIsToy((Wrap *)part))
            return true;
    }
    return false;
}

bool PapaXmasElf::tableHasBox() {
    std::vector<std::string> temp = this->_table->getTitles();
    bool to_return = false;

    for (const auto part : temp) {
        if (part == "Box")
            to_return = true;
    }
    return to_return;
}

bool PapaXmasElf::tableHasPaperGift() {
    std::vector<std::string> temp = this->_table->getTitles();
    bool to_return = false;

    for (const auto part : temp) {
        if (part == "GiftPaper")
            to_return = true;
    }
    return to_return;
}

bool PapaXmasElf::recIsToy(Wrap *wrap) {
    if (!wrap)
        return false;
    wrap->openMe();
    if (wrap->isWrap() && wrap->getContainedObject()) {
        if (wrap->getContainedObject()->getName() != "Box"
        && wrap->getContainedObject()->getName() != "GiftPaper")
        {
           wrap->closeMe();
           return true;
        };
        if (recIsToy((Wrap *)wrap->getContainedObject()))
        {
            wrap->closeMe();
            return true;
        }
        wrap->closeMe();
        return false;
    }
    wrap->closeMe();
    return false;
}

bool PapaXmasElf::isToyInBox(){
    return recIsToy((Wrap *)_hand.getObject());
}

int PapaXmasElf::toyPosition() {
    int i = 0;

    for (const auto part : _table->getAll()) {
        const auto wrap = (Wrap *)part;
        if (wrap->getName() == "Box" || wrap->getName() == "GiftPaper")
        { 
            if (recIsToy((Wrap *)part))
                return i;
        }
        ++i;
    }
    return -1;
}