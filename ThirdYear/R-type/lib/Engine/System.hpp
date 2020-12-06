#pragma once

// Project includes
#include "Component.hpp"
#include "ISystem.hpp"
#include "IEntity.hpp"

// C++ includes
#include <set>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief System Class.
     */
    class System : virtual public ISystem
    {
    public:
        System();
        ~System();

        virtual void Start() override;
        virtual void Update() override;
        virtual void UpdateEngine() override;
        virtual void Tick() override;
        virtual void OnEntityDestruction(EntityId id) override;

    public:
        bool started = false;

    public:
        std::set<EntityId> entityIds;
        std::set<EntityId> entityIdsToRemove;
        std::string systemName;
};
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
