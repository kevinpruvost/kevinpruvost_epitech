/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** PapaXmasTable
*/

#include "PapaXmasTable.hpp"

PapaXmasTable::PapaXmasTable()
{
}

PapaXmasTable::~PapaXmasTable()
{
}

bool PapaXmasTable::put(Object * object) {
    if (!_isColapsed) {
        this->_contained.push_back(object);
        if (_contained.size() > 10) {
            _isColapsed = true;
            std::cerr << "Table has collapsed" << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Table has already collapsed" << std::endl;
        return false;
    }
    return true;
}

Object * PapaXmasTable::take(int index) {
    if (!_isColapsed) {
        Object *temp = _contained.at(index);
        auto i = _contained.begin();
        for (int j = 0; j < index; j++, i++)
        this->_contained.erase(i);
        return temp;
    }
    return nullptr;
}

std::vector<std::string> PapaXmasTable::getTitles() {
    std::vector<std::string> temp;

    for (const auto part : _contained) {
        temp.push_back(part->getName());
    }
    return temp;
}

bool PapaXmasTable::isEmpty()
{
    return _contained.empty();
}

bool PapaXmasTable::isColapsed()
{
    return _isColapsed;
}

size_t PapaXmasTable::getSize()
{
    return _contained.size();
}

Object * PapaXmasTable::getBox()
{
    int i = 0;
    for (auto ite = _contained.begin(); ite != _contained.end();
                                            ++ite, ++i)
        if ((*ite)->getName() == "Box")
        {
            const auto get = _contained.at(i);
            _contained.erase(ite);
            return get;
        }
    return nullptr;
}

Object * PapaXmasTable::getGiftPaper()
{
    int i = 0;
    for (auto ite = _contained.begin(); ite != _contained.end();
                                            ++ite, ++i)
        if ((*ite)->getName() == "GiftPaper")
        {
            const auto get = _contained.at(i);
            _contained.erase(ite);
            return get;
        }
    return nullptr;
}

Object * PapaXmasTable::getToy()
{
    int i = 0;
    for (auto ite = _contained.begin(); ite != _contained.end();
                                            ++ite, ++i)
        if ((*ite)->getName() != "GiftPaper" && (*ite)->getName() != "Box")
        {
            const auto get = _contained.at(i);
            _contained.erase(ite);
            return get;
        }
    return nullptr;
}

std::vector<Object *> & PapaXmasTable::getAll() {
    return _contained;
}