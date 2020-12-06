#pragma once

// Project includes
#include "IEntity.hpp"
#include "IComponent.hpp"
#include "EntitySignature.hpp"

// C++ includes
#include <set>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Interface of EntityIdFactory
     */
    class IEntityIdFactory
    {
        public:
            virtual ~IEntityIdFactory() = default;

            virtual EntityId ReserveEntityId() = 0;
            virtual void FreeEntityId(const EntityId id) = 0;
            virtual void AddComponentSignature(const EntityId id, const ComponentSignature compSign) = 0;
            virtual void RemoveComponentSignature(const EntityId id, const ComponentSignature compSign) = 0;
            virtual void SetSignature(const EntityId id, const EntitySignature & signature) = 0;
            virtual EntitySignature GetSignature(const EntityId id) = 0;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType