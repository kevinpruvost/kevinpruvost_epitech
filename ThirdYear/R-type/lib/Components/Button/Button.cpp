/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Button
*/

#include "Button.hpp"

using namespace RType::Common::Engine;

Button::Button(REngine & engine)
    : RComponent (engine)
{
}

Button::~Button()
{
}

void Button::hasBeenPressed()
{
    if (__callbackFunction)
        __callbackFunction();
}

void Button::setCallback(const std::function<void ()> function)
{
    __callbackFunction = function;
}

void Button::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    /*auto convertedComponent = reinterpret_cast<Button *>(component);

    convertedComponent->ClassName();
    started = convertedComponent->started;
    id = convertedComponent->id;
    entityId = convertedComponent->entityId;
    _isHover = convertedComponent->_isHover;*/
}
