#pragma once

#include "Engine/RSystem.hpp"

#include "Components/Collider/Collider.hpp"
#include "Components/Collider/CircleCollider/CircleCollider.hpp"
#include "Components/Collider/RectangleCollider/RectangleCollider.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Example System class.
     */
    class ColliderSystem : virtual public RSystem
    {
    public:
        ColliderSystem(REngine & engine);
        ~ColliderSystem();

        void Start() override;
        void Update() override;
        void Tick() override;

        void TickByEntity(REntity& entity) override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
