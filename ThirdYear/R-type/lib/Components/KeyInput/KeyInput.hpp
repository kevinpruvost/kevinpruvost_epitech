#pragma once

#include "Engine/RComponent.hpp"

#include "Network/Rfc.hpp"

#include <functional>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains a vector mainly, and the slots linked to their behaviour.
     */
    class KeyInput : public RComponent
    {

        RCOMPONENT_MANDATORIES(KeyInput)

    public:
        KeyInput(REngine & engine);
        ~KeyInput();

        void Start() override;
        void Update() override;
        void Tick() override;

        void SetCallback(std::function<void()> callback);

        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

    public:
        bool inputCodes[102];
        Rfc::InputCode inputCode = Rfc::InputCode::Unknown;
        std::function<void()> callback;
        bool pressed = false;
        bool callBackOnPressed = true; // Else While pressed
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
