#include "REntity.hpp"

using namespace RType::Common::Engine;

REntity::REntity(REngine & engine)
    : RAccess(engine)
{
    _id = _engine.get().CreateEntityId();
}

REntity::REntity(REngine& engine, EntityId id)
    : RAccess(engine)
    , Entity(id)
{
    __idGiven = true;
}

REntity::REntity(const REntity& entity)
    : REntity(entity._engine)
{
}

REntity::~REntity()
{
    if (!__idGiven)
    {
        _engine.get().DestroyEntityId(_id);
    }
}

void REntity::Start()
{
}

void REntity::Tick()
{
}

void REntity::Update()
{
}

void REntity::UpdateEngine()
{
    Update();
}
