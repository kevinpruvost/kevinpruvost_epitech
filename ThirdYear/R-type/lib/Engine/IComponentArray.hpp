#pragma once

// Project includes
#include "Component.hpp"
#include "IEntity.hpp"

#include <list>
#include <memory>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Interface of Commponent Array.
     */
    class IComponentArray
    {
        public:
            virtual ~IComponentArray() = default;

            /**
             * Pure function that will inform the component array that an
             * entity of id 'id' has been destroyed.
             * 
             * \param id
             */
            virtual void EntityDestroyed(const EntityId id) = 0;

            virtual std::list<std::weak_ptr<Component>> GetConvertedComponents() = 0;

            virtual EntityId FindParentEntityWithComponent(const Component & comp) = 0;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType