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
    class Text : public RComponent
    {
        RCOMPONENT_MANDATORIES(Text)

    public:
        Text(REngine & engine);
        ~Text();

        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

    public:
        std::string text;
        std::string fontName;
        int fontSize;
        FontColor fontColor;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
