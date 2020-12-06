/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Background
*/

#pragma once

// Project includes
#include "Engine/REntity.hpp"
#include "Components/KeyInput/KeyInput.hpp"

#include <functional>

namespace RType
{
namespace Common
{
namespace Engine
{
    class Controller : public REntity
    {
        RENTITY_MANDATORIES(Controller)

    public:
        Controller(REngine & engine);
        ~Controller();

        void Start() override;

    public:
        std::function<void()> callbackOnKeyPressed;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType