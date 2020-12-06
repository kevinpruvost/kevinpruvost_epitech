#include "CircleCollider.hpp"

using namespace RType::Common::Engine;

CircleCollider::CircleCollider(REngine& engine)
    : Collider(engine)
{
    colliderType = ColliderType::Circle;
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
}

void CircleCollider::Tick()
{
}

CollisionData CircleCollider::GetCollisionData() const
{
    //if (_transform.expired()) throw CRITICAL_EXCEPTION("Transform does not exist anymore.")
    //auto transform = _transform.lock();

    Size sizediv = GetComponent<Transform>().vector.size / 2;
    CollisionData collisionData( GetComponent<Transform>().vector.position + sizediv, sizediv.x);
    return collisionData;
}

void CircleCollider::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    colliderType = updateRequest.colider.colliderType;
    colliderLayer = updateRequest.colider.colliderLayer;
}