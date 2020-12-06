#include "SystemFactory.hpp"

using namespace RType::Common::Engine;

SystemFactory::SystemFactory()
{
}

SystemFactory::~SystemFactory()
{
}

void SystemFactory::EntityDestroyed(EntityId id)
{
    for (auto & pair : __systemsByNames)
    {
        const auto & system = pair.second;

        system->OnEntityDestruction(id);
        system->entityIds.erase(id);
        system->entityIdsToRemove.insert(id);
    }
}

void SystemFactory::EntitySignatureChanged(EntityId id, const EntitySignature & entitySignature)
{
    DEBUG_LOG("Checking for " << id << ", because its signature changed.");
    for (auto& pair : __systemsByNames)
    {
        const auto & system = pair.second;
        const auto & systemSignature = __signaturesBySystemNames[pair.first];

        if (entitySignature | systemSignature)
            system->entityIds.insert(id);
        else
            system->entityIds.erase(id);
    }
}

std::list<std::weak_ptr<System>> SystemFactory::GetEverySystems()
{
    std::list<std::weak_ptr<System>> systems;

    std::transform(__systemsByNames.begin(), __systemsByNames.end(), std::back_inserter(systems),
        [](const std::pair<std::string, std::shared_ptr<System>>& system) -> std::shared_ptr<System> {
        return system.second;
    });
    return systems;
}
