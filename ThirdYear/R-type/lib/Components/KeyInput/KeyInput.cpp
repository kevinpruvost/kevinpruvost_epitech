#include "KeyInput.hpp"

using namespace RType::Common::Engine;

KeyInput::KeyInput(REngine& engine)
    : RComponent(engine)
{
    for (int i = 0; i < 102; ++i)
    {
        inputCodes[i] = false;
    }
}

KeyInput::~KeyInput()
{
}

void KeyInput::Start()
{
}

void KeyInput::Update()
{
    if (pressed)
    {
        if (callback)
            callback();
        if (callBackOnPressed)
            pressed = false;
    }
}

void KeyInput::Tick()
{
}

void KeyInput::SetCallback(std::function<void()> newCallback)
{
    callback = newCallback;
}

void KeyInput::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    /*auto convertedComponent = reinterpret_cast<KeyInput *>(component);

    convertedComponent->ClassName();
    started = convertedComponent->started;
    id = convertedComponent->id;
    entityId = convertedComponent->entityId;
    for (int i = 0; i < 102; ++i)
        inputCodes[i] = convertedComponent->inputCodes[i];
    pressed = convertedComponent->pressed;
    callBackOnPressed = convertedComponent->callBackOnPressed;*/
}
