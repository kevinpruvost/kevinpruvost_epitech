/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Supply.hpp"

Supply::Supply(Types type, size_t amount)
    : Type { type }
    , Amount { amount }
    , Wrecks { nullptr }
{

}

Supply::Supply(Types type, size_t amount, Droid ** wrecks)
    : Type { type }
    , Amount { amount }
    , Wrecks { wrecks }
{

}

Supply::~Supply()
{
    if (!Wrecks)
        return;
    for (size_t i = 0; Wrecks[i] != nullptr;)
    {
        if (Wrecks[i]->_msg == 0)
        {
            ++i;
            continue;
        }
        delete Wrecks[i];
        Wrecks[i++] = nullptr;
    }
    delete Wrecks;
    Wrecks = nullptr;
}

//Supply & Supply::operator->()
//{
//    return *this;
//}

Droid * Supply::operator->()
{
    return Wrecks[index];
}

Droid & Supply::operator*()
{
    return *Wrecks[index];
}

Supply & Supply::operator++()
{
    ++index;
    if (index >= (int)getWrecksSize())
        index = 0;
    return *this;
}

Supply & Supply::operator--()
{
    --index;
    if (index < 0)
        index = getWrecksSize() - 1;
    return *this;
}

Supply::operator size_t()
{
    return Amount;
}

Supply & Supply::operator!()
{
    Amount = 0;
    if (!Wrecks)
        return *this;
    for (size_t i = 0; Wrecks[i] != nullptr;)
    {
        if (Wrecks[i]->_msg == 0)
        {
            ++i;
            continue;
        }
        delete Wrecks[i];
        Wrecks[i++] = nullptr;
    }
    return *this;
}

bool Supply::operator==(const Supply & supply) const
{
    if (supply.getType() == Type)
        return true;
    return false;
}

bool Supply::operator==(const Types & type) const
{
    if (type == Type)
        return true;
    return false;
}

bool Supply::operator!=(const Supply & supply) const
{
    if (supply.getType() != Type)
        return true;
    return false;
}

bool Supply::operator!=(const Types & type) const
{
    if (type != Type)
        return true;
    return false;
}

// Stand-alone Operators -------------------------------------------------------

std::ostream & operator<<(std::ostream & os, Supply & supply)
{
    if (supply.getType() == Supply::Types::Wreck)
    {
        os << "Supply : " << supply.getWrecksSize() << ", Wreck";
        if (!supply.getWrecks())
            return os;
        for (size_t i = 0; supply.getWreck(i) != nullptr; ++i)
            os << std::endl << *(supply.getWreck(i));
    }
    else
    {
        std::string type = (supply.getType() == Supply::Types::Iron)
                           ? "Iron" : "Silicon";
        os << "Supply : " << supply.getAmount() << ", " << type;
    }
    return os;
}

// Getters and setters ---------------------------------------------------------

size_t Supply::getWrecksSize() const
{
    size_t ret = 0;
    if (!Wrecks)
        return ret;
    while (Wrecks[ret] != nullptr)
        ++ret;
    return ret;
}

size_t Supply::getAmount() const { return Amount; }

int Supply::getIndex() const { return index; }

Supply::Types Supply::getType() const { return Type; }

void Supply::setType(Types type) { Type = type; }

void Supply::setAmount(size_t amount) { Amount = amount; }

void Supply::setWrecks(Droid ** wrecks) { Wrecks = wrecks; }

void Supply::setIndex(int id) { index = id; }

Droid ** Supply::getWrecks() const { return Wrecks; }

Droid * Supply::getWreck(size_t index) const
{
    if (!Wrecks)
        return nullptr;
    return Wrecks[index];
}
