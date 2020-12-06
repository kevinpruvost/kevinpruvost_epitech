#pragma once

#include "Components/Transform/Transform.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains a vector mainly, and the slots linked to their behaviour.
     */
    class UITransform : public RComponent
    {
        RCOMPONENT_MANDATORIES(UITransform)

    public:
        UITransform(REngine & engine);
        ~UITransform();

        void Start() override;
        void Update() override;
        void Tick() override;

        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

    public:
        Point position = { 0.f, 0.f };
        Size size = { 0.f, 0.f };

        bool centered = false;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
