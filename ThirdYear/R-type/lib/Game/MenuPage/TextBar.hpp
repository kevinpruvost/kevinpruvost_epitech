/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TextInput
*/

#pragma once

#include "Engine/REntity.hpp"
#include "lib/Entities/UI/UITextInput/UITextInput.hpp"
#include "Chronometer.hpp"

#include <functional>

namespace RType
{
namespace Common
{
namespace Engine
{
    class TextBar : public UITextInput
    {

        RENTITY_MANDATORIES(TextBar)

        public:
            TextBar(REngine & engine);
            ~TextBar();

            void Start() override;
            void Update() override;
            void SetTextBarCallback(std::function<void()> callback);

        private:
            std::weak_ptr<UITransform> __transform;
            std::weak_ptr<Text> __input;
            bool display = false;
            Chronometer chrono;
            std::function<void()> __textBarCallback;
    };
};
};
};
