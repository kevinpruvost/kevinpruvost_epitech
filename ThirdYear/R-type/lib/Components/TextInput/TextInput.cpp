/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TextInput
*/

#include "TextInput.hpp"

using namespace RType::Common::Engine;

TextInput::TextInput(REngine & engine)
    : RComponent(engine)
{
}

TextInput::~TextInput()
{
}

void TextInput::addCharacter(char charac)
{
    GetComponent<Text>().text += (charac);
}

void TextInput::addString(const std::string & str)
{
    GetComponent<Text>().text.append(str);
}

void TextInput::deleteLastCharacter()
{
    GetComponent<Text>().text = GetComponent<Text>().text.substr(0, GetComponent<Text>().text.size() - 1);
}

void TextInput::deleteLastXCharacter(unsigned int x)
{
    GetComponent<Text>().text = GetComponent<Text>().text.substr(0, GetComponent<Text>().text.size() - x);
}

void TextInput::addKeyInput()
{
    RType::Common::Rfc::InputCode inputCode = GetComponent<KeyInput>().inputCode;

    if (GetComponent<Text>().text.size() >= maxSize && (inputCode != RType::Common::Rfc::InputCode::Backspace && inputCode != RType::Common::Rfc::InputCode::Enter))
        return;

    switch (inputCode)
    {
        case RType::Common::Rfc::InputCode::Num1:
            addCharacter('1');
            break;
        case RType::Common::Rfc::InputCode::Num2:
            addCharacter('2');
            break;
        case RType::Common::Rfc::InputCode::Num3:
            addCharacter('3');
            break;
        case RType::Common::Rfc::InputCode::Num4:
            addCharacter('4');
            break;
        case RType::Common::Rfc::InputCode::Num5:
            addCharacter('5');
            break;
        case RType::Common::Rfc::InputCode::Num6:
            addCharacter('6');
            break;
        case RType::Common::Rfc::InputCode::Num7:
            addCharacter('7');
            break;
        case RType::Common::Rfc::InputCode::Num8:
            addCharacter('8');
            break;
        case RType::Common::Rfc::InputCode::Num9:
            addCharacter('9');
            break;
        case RType::Common::Rfc::InputCode::Num0:
            addCharacter('0');
            break;
        case RType::Common::Rfc::InputCode::Equal:
            addCharacter('=');
            break;
        case RType::Common::Rfc::InputCode::Backspace:
            deleteLastCharacter();
            break;
        case RType::Common::Rfc::InputCode::A:
            addCharacter(capslock == true ? 'A' : 'a');
            break;
        case RType::Common::Rfc::InputCode::Z:
            addCharacter(capslock == true ? 'Z' : 'z');
            break;
        case RType::Common::Rfc::InputCode::E:
            addCharacter(capslock == true ? 'E' : 'e');
            break;
        case RType::Common::Rfc::InputCode::R:
            addCharacter(capslock == true ? 'R' : 'r');
            break;
        case RType::Common::Rfc::InputCode::T:
            addCharacter(capslock == true ? 'T' : 't');
            break;
        case RType::Common::Rfc::InputCode::Y:
            addCharacter(capslock == true ? 'Y' : 'y');
            break;
        case RType::Common::Rfc::InputCode::U:
            addCharacter(capslock == true ? 'U' : 'u');
            break;
        case RType::Common::Rfc::InputCode::I:
            addCharacter(capslock == true ? 'I' : 'i');
            break;
        case RType::Common::Rfc::InputCode::O:
            addCharacter(capslock == true ? 'O' : 'o');
            break;
        case RType::Common::Rfc::InputCode::P:
            addCharacter(capslock == true ? 'P' : 'p');
            break;
        case RType::Common::Rfc::InputCode::Q:
            addCharacter(capslock == true ? 'Q' : 'q');
            break;
        case RType::Common::Rfc::InputCode::S:
            addCharacter(capslock == true ? 'S' : 's');
            break;
        case RType::Common::Rfc::InputCode::D:
            addCharacter(capslock == true ? 'D' : 'd');
            break;
        case RType::Common::Rfc::InputCode::F:
            addCharacter(capslock == true ? 'F' : 'f');
            break;
        case RType::Common::Rfc::InputCode::G:
            addCharacter(capslock == true ? 'G' : 'g');
            break;
        case RType::Common::Rfc::InputCode::H:
            addCharacter(capslock == true ? 'H' : 'h');
            break;
        case RType::Common::Rfc::InputCode::J:
            addCharacter(capslock == true ? 'J' : 'j');
            break;
        case RType::Common::Rfc::InputCode::K:
            addCharacter(capslock == true ? 'K' : 'k');
            break;
        case RType::Common::Rfc::InputCode::L:
            addCharacter(capslock == true ? 'L' : 'l');
            break;
        case RType::Common::Rfc::InputCode::M:
            addCharacter(capslock == true ? 'M' : 'm');
            break;
        case RType::Common::Rfc::InputCode::Multiply:
            addCharacter('*');
            break;
        case RType::Common::Rfc::InputCode::LBracket:
            addCharacter('{');
            break;
        case RType::Common::Rfc::InputCode::W:
            addCharacter(capslock == true ? 'W' : 'w');
            break;
        case RType::Common::Rfc::InputCode::X:
            addCharacter(capslock == true ? 'X' : 'x');
            break;
        case RType::Common::Rfc::InputCode::C:
            addCharacter(capslock == true ? 'C' : 'c');
            break;
        case RType::Common::Rfc::InputCode::V:
            addCharacter(capslock == true ? 'V' : 'v');
            break;
        case RType::Common::Rfc::InputCode::B:
            addCharacter(capslock == true ? 'B' : 'b');
            break;
        case RType::Common::Rfc::InputCode::N:
            addCharacter(capslock == true ? 'N' : 'n');
            break;
        case RType::Common::Rfc::InputCode::Semicolon:
            addCharacter(';');
            break;
        case RType::Common::Rfc::InputCode::Enter:
            if (callbackOnEnter)
                callbackOnEnter();
            break;
        /*case RType::Common::Rfc::InputCode::KEY_NUM_0:
            addCharacter('0');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_1:
            addCharacter('1');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_2:
            addCharacter('2');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_3:
            addCharacter('3');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_4:
            addCharacter('4');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_5:
            addCharacter('5');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_6:
            addCharacter('6');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_7:
            addCharacter('7');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_8:
            addCharacter('8');
            break;
        case RType::Common::Rfc::InputCode::KEY_NUM_9:
            addCharacter('9');
            break;*/
        case RType::Common::Rfc::InputCode::Divide:
            addCharacter('/');
            break;
        /*case RType::Common::Rfc::InputCode::Multiply:
            addCharacter('*');
            break;*/
        case RType::Common::Rfc::InputCode::Subtract:
            addCharacter('-');
            break;
        case RType::Common::Rfc::InputCode::Add:
            addCharacter('+');
            break;
        case RType::Common::Rfc::InputCode::Period:
            addCharacter('.');
            break;
        default:
            break;
    }
}

void TextInput::linkToKeyInput()
{
    auto & keyInput = GetComponent<KeyInput>();
    for (int i = 0; i < 102; ++i)
        keyInput.inputCodes[i] = true;
    keyInput.SetCallback([this](){
        addKeyInput();
    });
}

void TextInput::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
}