/*
** EPITECH PROJECT, 2020
** Factory.cpp
** File description:
** factory src
*/

#include "Factory.hpp"

using namespace nts;

Factory::Factory()
{
}

std::unique_ptr<IComponent> Factory::createComponent(const std::string & type,
                                                     const std::string & name)
{
         if (type == "input")  return createInput(name);
    else if (type == "clock")  return createClock(name);
    else if (type == "true")   return createTrue(name);
    else if (type == "false")  return createFalse(name);
    else if (type == "output") return createOutput(name);
    else if (type == "terminal")   return createChar(name);
    else if (type == "2716")   return create2716(name);
    else if (type == "4001")   return create4001(name);
    else if (type == "4008")   return create4008(name);
    else if (type == "4011")   return create4011(name);
    else if (type == "4013")   return create4013(name);
    else if (type == "4017")   return create4017(name);
    else if (type == "4030")   return create4030(name);
    else if (type == "4040")   return create4040(name);
    else if (type == "4069")   return create4069(name);
    else if (type == "4071")   return create4071(name);
    else if (type == "4081")   return create4081(name);
    else if (type == "4094")   return create4094(name);
    else if (type == "4514")   return create4514(name);
    else if (type == "4801")   return create4801(name);
    else
    {
        throw EXCEPTION("How the fuck did you get here ?");
        return createInput("BUG");
    }
}