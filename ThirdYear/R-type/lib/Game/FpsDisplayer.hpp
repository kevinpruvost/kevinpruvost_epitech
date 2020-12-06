/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Object
*/

#pragma once

// Project includes
#include "Engine/REntity.hpp"
#include "Entities/UI/UIText/UIText.hpp"

#include <limits>

namespace RType
{
namespace Common
{
namespace Engine
{
    class FpsDisplayer : public UIText
    {
        RENTITY_MANDATORIES(FpsDisplayer)

    public:
        FpsDisplayer(REngine & engine);
        ~FpsDisplayer();

        void Start() override;
        void Update() override;
        
    private:
        std::weak_ptr<Text> __text;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType