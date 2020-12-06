/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TextInput
*/

#include "TextBar.hpp"

using namespace RType::Common::Engine;

TextBar::TextBar(REngine & engine)
    : UITextInput(engine)
{
}

TextBar::~TextBar()
{
}

void TextBar::Start()
{
    UITextInput::Start();
    __transform = GetComponentPtr<UITransform>();
    __input = GetComponentPtr<Text>();

    if (__transform.expired()) return;
    if (__input.expired()) return;

    auto& text = GetComponent<Text>();
    text.fontName = "default_font";
    text.fontSize = 30;
    text.fontColor = { 0, 255, 0 };

    auto transform = __transform.lock();

    transform->size.x = 0.25;
    transform->size.y = 0.1;
    transform->position.x = 0.5;
    transform->position.y = 0.685;

    chrono.start();

    GetComponent<TextInput>().callbackOnEnter = __textBarCallback;
}

void TextBar::Update()
{
    if (__transform.expired()) return;
    if (__input.expired()) return;

    auto transform = __transform.lock();
    auto input = __input.lock();

    int sizeText = input->text.size();
    float seconds = chrono.getPastTimeInSeconds();

    if (sizeText > 1 && input->text[0] == '|') {
        input->text.erase(0, 1);
        display = false;
    }

    if (display && input->text == "|" && seconds >= 0.3) {
        input->text.erase(0, 1);
        display = false;
    } else if (sizeText == 0 && seconds > 0 && seconds <= 0.3) {
        display = true;
        input->text = "|";
    }

    if (seconds >= 0.6)
        chrono.start();

    transform->position.x = 0.5 - ((0.01 * input->text.size()) / 2);
}

void TextBar::SetTextBarCallback(std::function<void()> callback)
{
    __textBarCallback = callback;
}
