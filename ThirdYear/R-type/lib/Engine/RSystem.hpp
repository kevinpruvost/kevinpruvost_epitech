#pragma once

// Project includes
#include "RAccess.hpp"
#include "REntity.hpp"

// C++ includes
#include <functional>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief System derivation that aims to be a simplified version of System
     * to handle, it has more practical methods to use.
     */
    class RSystem : virtual public System, public RAccess
    {
    public:
        RSystem(REngine & engine);
        ~RSystem();

        virtual void Start() override;
        virtual void Update() override;
        virtual void Tick() override;
        virtual void UpdateEngine() final override;

        virtual void TickByEntity(REntity & entity);

        virtual void OnEntityDestruction(EntityId id) override;

        /**
         * @brief Adds a component signature to the system.
         *
         * \param signature
         */
        template<typename T>
        void AddComponentSignature()
        {
            _engine.get().AddComponentSignatureToSystem(systemName, _engine.get().GetComponentSignature<T>());
        }

    protected:
        std::unordered_map<EntityId, std::shared_ptr<REntity>> _entities;
};
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
