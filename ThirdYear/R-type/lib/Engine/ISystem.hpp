#pragma once

#include "IEntity.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    using SystemId = unsigned int;

    /**
     * @brief Interface of System.
     */
    class ISystem
    {
        public:
            virtual ~ISystem() = default;

            /**
             * @brief Pure function used by the REngine.
             * Its purpose is to be overriden by the children classes, mainly by RComponent direct children.
             */
            virtual void Update() = 0;
            /**
             * @brief Pure function used by the REngine, launched on every turn of the game loop.
             * Its purpose is to be overriden by RComponent, UpdateEngine() will mainly call Update() and do some other corrections
             */
            virtual void UpdateEngine() = 0;
            /**
             * @brief Pure function used by the REngine, launched at the first frame where the object is created
             */
            virtual void Start() = 0;
            /**
             * @brief Pure function used by the REngine, launched at each tick of the game loop.
             */
            virtual void Tick() = 0;
            /**
             * @brief launched at entity destruction
             * \param id
             */
            virtual void OnEntityDestruction(EntityId id) = 0;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
