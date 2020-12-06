#pragma once

#include "Engine/RComponent.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains a vector mainly, and the slots linked to their behaviour.
     */
    class Sprite : public RComponent
    {
        RCOMPONENT_MANDATORIES(Sprite)

    public:
        Sprite(REngine & engine);
        ~Sprite();

        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

    public:
        std::string spriteName;
        SpriteColor color;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
