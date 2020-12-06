#include "EntityIdFactory.hpp"

// Project includes
#include "Exception.hpp"
#include "DebugController.hpp"

// C++ includes
#include <climits>

using namespace RType::Common::Engine;

EntityIdFactory::EntityIdFactory()
    : __movingId (0)
{
}

EntityIdFactory::~EntityIdFactory()
{
    __destroying = true;
    __entityCopiesByClassName.clear();
    __entities.clear();
}

EntityId EntityIdFactory::ReserveEntityId()
{
    EntityId idToGive;

    if (__freeIds.size() != 0)
    {
        idToGive = *__freeIds.begin();
        __freeIds.erase(idToGive);
    }
    else
    {
        idToGive = __movingId++;
    }

    if (idToGive >= UINT_MAX)
    {
        throw CRITICAL_EXCEPTION("Maximum number of entities reached. The program will now close for security purpose.");
    }

    __componentSignaturesByIds.insert({ idToGive, EntitySignature() });

    DEBUG_LOG("Id " << idToGive << " allocated !");
    LOG_INFO("Id " << idToGive << " allocated !");

    return idToGive;
}

EntityId EntityIdFactory::ReserveEntityId(EntityId id)
{
    EntityId idToGive = id;

    if (__freeIds.find(id) != __freeIds.end())
    {
        idToGive = id;
        __freeIds.erase(idToGive);
    }
    else
    {
        if (id >= __movingId)
        {
            idToGive = id;
            ++__movingId;
        }
    }

    if (idToGive >= UINT_MAX)
    {
        throw CRITICAL_EXCEPTION("Maximum number of entities reached. The program will now close for security purpose.");
    }

    __componentSignaturesByIds.insert({ idToGive, EntitySignature() });

    DEBUG_LOG("Id " << idToGive << " allocated !");
    LOG_INFO("Id " << idToGive << " allocated !");

    return idToGive;
}

void EntityIdFactory::FreeEntityId(const EntityId id)
{
    __freeIds.insert(id);

    if (__componentSignaturesByIds.find(id) != __componentSignaturesByIds.end())
        __componentSignaturesByIds.erase(id);
    if (!__destroying && __entities.find(id) != __entities.end())
        __entities.erase(id);

    LOG_INFO("Id " << id << " freed !");
    DEBUG_LOG("Id " << id << " freed !");
}

void EntityIdFactory::AddComponentSignature(const EntityId id, const ComponentSignature compSign)
{
    if (__freeIds.find(id) == __freeIds.end())
        throw CRITICAL_EXCEPTION("Trying to add component signature to non-existant entity.");

    if (__componentSignaturesByIds.find(id) == __componentSignaturesByIds.end())
        __componentSignaturesByIds.insert({ id, EntitySignature( {compSign}) });
    else
        __componentSignaturesByIds[id].insert(compSign);
}

void EntityIdFactory::RemoveComponentSignature(const EntityId id, const ComponentSignature compSign)
{
    if (__freeIds.find(id) == __freeIds.end())
        throw CRITICAL_EXCEPTION("Trying to remove component signature to non-existant entity.");

    if (__componentSignaturesByIds.find(id) == __componentSignaturesByIds.end())
        throw MINOR_EXCEPTION("Trying to remove already removed component signature.s");

    __componentSignaturesByIds[id].erase(compSign);
}

void EntityIdFactory::SetSignature(const EntityId id, const EntitySignature & signature)
{
    if (__componentSignaturesByIds.find(id) == __componentSignaturesByIds.end())
        throw CRITICAL_EXCEPTION("Trying to set component signature to non-existant entity.");

    __componentSignaturesByIds[id] = signature;
}

EntitySignature EntityIdFactory::GetSignature(const EntityId id)
{
    if (__componentSignaturesByIds.find(id) == __componentSignaturesByIds.end())
        throw MINOR_EXCEPTION("Trying to get component signature from non-existant entity '" + std::to_string(id) + "'.");

    return __componentSignaturesByIds[id];
}

std::vector<std::string> RType::Common::Engine::EntityIdFactory::GetEntityTypesNames()
{
    std::vector<std::string> names;
    for (auto& pair : __entityCopiesByClassName)
    {
        names.push_back(pair.first);
    }
    return names;
}

Entity & EntityIdFactory::CreateEntityFromClassName(const std::string& name)
{
    if (__entityCopiesByClassName.find(name) == __entityCopiesByClassName.end())
        throw CRITICAL_EXCEPTION("Trying to create non-existent Entity of name : " + name);

    auto ptr = std::shared_ptr<Entity>(__entityCopiesByClassName[name]->ProperCopy());
    EntityId newId = ptr->getId();
    __entities.insert({ newId, ptr });
    LOG_INFO("Created " << __entities.at(newId)->ClassName());
    return *__entities.at(newId);
}

Entity & EntityIdFactory::Instantiate(const std::string& name)
{
    return CreateEntityFromClassName(name);
}

std::list<std::weak_ptr<Entity>> EntityIdFactory::GetEveryEntities()
{
    std::list<std::weak_ptr<Entity>> entities;

    std::transform(__entities.begin(), __entities.end(), std::back_inserter(entities),
        [](const std::pair<EntityId, std::shared_ptr<Entity>>& entity) -> std::weak_ptr<Entity> {
        return entity.second;
    });
    return entities;
}

std::weak_ptr<Entity> EntityIdFactory::StockEntity(Entity& entity)
{
    __entities.insert({ entity.getId(), std::shared_ptr<Entity>(entity.ProperCopy()) });
    return __entities[entity.getId()];
}

bool EntityIdFactory::HasEntityInStock(EntityId id)
{
    return __entities.find(id) != __entities.end();
}

void EntityIdFactory::DestroyAll()
{
    std::vector<EntityId> toFree;

    for (auto& pair : __entities)
        toFree.push_back(pair.first);

    for (auto id : toFree)
        FreeEntityId(id);

    __movingId = 0;
    __destroying = false;
}
