/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** UITextInput
*/

#include "UITextInput.hpp"

using namespace RType::Common::Engine;

UITextInput::UITextInput(REngine & engine)
    : UI (engine)
{
}

UITextInput::~UITextInput()
{
}

void UITextInput::Start()
{
    UI::Start();
    AddComponent<TextInput>();
    AddComponent<Text>();
    AddComponent<KeyInput>();

    GetComponent<TextInput>().linkToKeyInput();
}