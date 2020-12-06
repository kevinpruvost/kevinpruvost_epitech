#pragma once

#include "Engine/RComponent.hpp"
#include "Components/Transform/Transform.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class CollisionData
    {
    public:
        CollisionData(Point p1, Point p2)
            : colliderType{ ColliderType::Rectangle }, point1{ p1 }, point2{ p2 } {}
        CollisionData(Point p1, float r)
            : colliderType{ ColliderType::Circle }, point1{ p1 }, radius{ r } {}
        ColliderType colliderType;
        Point point1;
        union
        {
            float radius;
            Point point2;
        };
    };
    /**
     * @brief Contains a vector mainly, and the slots linked to their behaviour.
     */
    class Collider : public RComponent
    {
        RCOMPONENT_MANDATORIES(Collider)

    public:
        Collider(REngine & engine);
        ~Collider();

        void Start() final override;
        void Update() override;
        void Tick() override;

        virtual CollisionData GetCollisionData() const = 0;
        void OnCollision(const Collider & collidedCollider);
        bool IsCollidingWith(const Collider& othercollider) const;
        void FixPosition(const Collider & obstacle);
    private:
        Point FixPositionBetweenRectangleAndCircle(const CollisionData & rect, const CollisionData& circle);
    public:
        bool IsRectangleCollidingWithCircle(const Point & leftTop, const Point & bottomRight, const Point & circleCenter, float circleRadius) const;
        bool IsRectangleCollidingWithRectangle(const Point& leftTop1, const Point& bottomRight1, const Point& leftTop2, const Point& bottomRight2) const;
        bool IsCircleCollidingWithCircle(const Point& circleCenter1, float circleRadius1, const Point& circleCenter2, float circleRadius2) const;

        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

    public:
        ColliderType colliderType;
        ColliderLayer colliderLayer = ColliderLayer::NoLayer;
        std::function<void(const Collider&)> callbackOnCollision = nullptr;

    protected:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
