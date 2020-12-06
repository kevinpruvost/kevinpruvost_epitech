/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Object
*/

#pragma once

// Project includes
#include "Engine/REntity.hpp"
#include "Entities/UI/UIImage/UIImage.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class TitleScreen : public UIImage
    {
        RENTITY_MANDATORIES(TitleScreen)

    public:
        TitleScreen(REngine & engine);
        ~TitleScreen();

        void Start() override;
        void Update() override;
        
    private:
        std::weak_ptr<UITransform> __transform;

        Size __baseSize;
        bool __sens = true;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType