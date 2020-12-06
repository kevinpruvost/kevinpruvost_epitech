#include "RectangleCollider.hpp"

using namespace RType::Common::Engine;

RectangleCollider::RectangleCollider(REngine& engine)
    : Collider(engine)
{
    colliderType = ColliderType::Rectangle;
}

RectangleCollider::~RectangleCollider()
{
}

void RectangleCollider::Update()
{
}

void RectangleCollider::Tick()
{
}

CollisionData RectangleCollider::GetCollisionData() const
{
    //if (_transform.expired()) throw CRITICAL_EXCEPTION("Transform does not exist anymore.");

    //auto transform = _transform.lock();

    CollisionData collisionData(
         GetComponent<Transform>().vector.position,
         GetComponent<Transform>().vector.position + GetComponent<Transform>().vector.size
    );
    return collisionData;
}

void RectangleCollider::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    colliderType = updateRequest.colider.colliderType;
    colliderLayer = updateRequest.colider.colliderLayer;
}
