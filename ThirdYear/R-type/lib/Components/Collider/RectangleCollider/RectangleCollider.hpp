#pragma once

#include "Components/Collider/Collider.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains a vector mainly, and the slots linked to their behaviour.
     */
    class RectangleCollider : public Collider
    {
        RCOMPONENT_MANDATORIES(RectangleCollider)

    public:
        RectangleCollider(REngine & engine);
        ~RectangleCollider();

        void Update() override;
        void Tick() override;

        CollisionData GetCollisionData() const override;

        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

    public:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
