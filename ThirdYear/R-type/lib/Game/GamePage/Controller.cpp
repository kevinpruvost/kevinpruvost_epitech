/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Background
*/

#include "Controller.hpp"

using namespace RType::Common::Engine;

Controller::Controller(REngine& engine)
    : REntity(engine)
{
}

Controller::~Controller()
{
}

void Controller::Start()
{
    AddComponent<KeyInput>();
    auto& keyInput = GetComponent<KeyInput>();
    keyInput.callBackOnPressed = true;
    for (int i = 0; i < 102; ++i)
        keyInput.inputCodes[i] = true;
    keyInput.callback = callbackOnKeyPressed;
}
