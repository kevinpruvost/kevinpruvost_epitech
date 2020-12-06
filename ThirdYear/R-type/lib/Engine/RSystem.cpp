#include "RSystem.hpp"

using namespace RType::Common::Engine;

extern std::unique_ptr<REngine> globalEngine;

RSystem::RSystem(REngine & engine)
    : RAccess(engine)
{
}

RSystem::~RSystem()
{
}

void RSystem::Start()
{
}

void RSystem::Update()
{
}

void RSystem::Tick()
{
}

void RSystem::UpdateEngine()
{
    DEBUG_LOG(typeid(*this).name() << " : UpdateEngine()");

    if (!entityIdsToRemove.empty())
    {
        for (auto& id : entityIdsToRemove)
        {
            _entities.erase(id);
        }
        entityIdsToRemove.clear();
    }

    if (entityIds.size() != _entities.size())
    {
        for (auto& entityId : entityIds)
        {
            if (_entities.find(entityId) == _entities.end())
            {
                auto pair = std::make_pair(entityId, std::make_shared<REntity>(_engine, entityId));
                _entities.insert(pair);
                pair.second->started = GetEntity(pair.first).started;
            }
        }
    }

    DEBUG_LOG(typeid(*this).name() << " : UpdateEngine() : There is " << _entities.size() << " entities on this system.");

    for (auto& pair : _entities)
    {
        if (!pair.second->started)
        {
            pair.second->started = GetEntity(pair.first).started;
            LOG_INFO("oui bjr");
            if (!pair.second->started)
                continue;
            LOG_INFO("oui ok bisous");
        }
        DEBUG_LOG(typeid(*this).name() << " : UpdateEngine() : Ticking on entity " << pair.second->getId());
        TickByEntity(*pair.second);
    }

    DEBUG_LOG(typeid(*this).name() << " : UpdateEngine() : Update() launched.");
    Update();
}

void RSystem::TickByEntity(REntity & )
{

}

void RSystem::OnEntityDestruction(EntityId id)
{
}
