#include "ColliderSystem.hpp"

using namespace RType::Common::Engine;

ColliderSystem::ColliderSystem(REngine& engine)
    : RSystem(engine)
{
}

ColliderSystem::~ColliderSystem()
{
}

void ColliderSystem::Start()
{
    AddComponentSignature<RectangleCollider>();
    AddComponentSignature<CircleCollider>();
}

void ColliderSystem::Update()
{
}

void ColliderSystem::Tick()
{
}

void ColliderSystem::TickByEntity(REntity& entity)
{
    auto & myTransform = entity.GetComponent<Transform>();

//    if (myTransform.isStatic || !myTransform.hasMoved) return;

    myTransform.hasMoved = false;

    Collider* myCollider = nullptr;
    if (entity.HasComponent<CircleCollider>())
        myCollider = reinterpret_cast<Collider*>(&entity.GetComponent<CircleCollider>());
    else
        myCollider = reinterpret_cast<Collider*>(&entity.GetComponent<RectangleCollider>());


    if (myCollider == nullptr)
        throw CRITICAL_EXCEPTION("Collider not identified.");

    if (myCollider->colliderLayer == ColliderLayer::Obstacle
     || myCollider->colliderLayer == ColliderLayer::Pickable)
        return;

    for (auto& pair : _entities)
    {
        auto & checkEntity = *pair.second;

        if (checkEntity == entity)
            continue;

        Collider* checkCollider = nullptr;
        if (checkEntity.HasComponent<CircleCollider>())
            checkCollider = reinterpret_cast<Collider *>(&checkEntity.GetComponent<CircleCollider>());
        else
            checkCollider = reinterpret_cast<Collider*>(&checkEntity.GetComponent<RectangleCollider>());

        if (myCollider->IsCollidingWith(*checkCollider))
        {
            DEBUG_LOG("Collision between " << entity.getId() << " and " << checkEntity.getId());
            myCollider->OnCollision(*checkCollider);
        }
    }    
}
