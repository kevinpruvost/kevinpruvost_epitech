#include "Entity.hpp"

// Project includes
#include "Exception.hpp"

using namespace RType::Common::Engine;

Entity::Entity()
    : _id { 0 }
{
}

Entity::Entity(EntityId id)
    : _id { id }
{

}

Entity::~Entity()
{
}

void Entity::Start()
{

}

void Entity::Update()
{

}

void Entity::Tick()
{
}

void Entity::UpdateEngine()
{
}

EntityId Entity::getId() const { return _id; }

void Entity::setId(const EntityId id) { _id = id; }

std::string RType::Common::Engine::Entity::ClassName()
{
    return _className;
}
