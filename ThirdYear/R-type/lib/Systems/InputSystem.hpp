/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InputSystem
*/

#pragma once

#include "Engine/RSystem.hpp"
#include "Components/KeyInput/KeyInput.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Input System Class
     * 
     */
    class InputSystem : virtual public RSystem {
        public:
            InputSystem(REngine & engine);
            ~InputSystem();

            void Start() override;
            void Update() override;
            void Tick() override;

            void TickByEntity(REntity& entity) override;

        protected:
        private:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
