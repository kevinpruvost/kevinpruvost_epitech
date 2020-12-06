#pragma once

// Project includes
#include "REngine.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Serves as an accesser to all things in the REngine.
     */
    class RAccess
    {
    public:
        RAccess(REngine& engine) : _engine{ engine } { }
        ~RAccess() = default;

        /**
         * @brief Used to get every components of a type T
         * \return
         */
        template<typename T>
        std::list<std::weak_ptr<T>> FindComponents()
        {
            return _engine.get().FindComponents<T>();
        }

        float DeltaTime()
        {
            return _engine.get().deltaTime;
        }

        bool EntityExists(const EntityId id)
        {
            return _engine.get().EntityExists(id);
        }

        Entity & GetEntity(const EntityId id)
        {
            return _engine.get().GetEntity(id);
        }

        std::shared_ptr<Entity> GetEntityPtr(const EntityId id)
        {
            return _engine.get().GetEntityPtr(id);
        }

    protected:
        std::reference_wrapper<REngine> _engine;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType