#pragma once

#include "Engine/REntity.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Example Entity class.
     */
    class ExampleEntity : virtual public REntity
    {
        RENTITY_MANDATORIES(ExampleEntity)

    public:
        ExampleEntity(REngine & engine);
        ~ExampleEntity();

        void Start() override;
        void Update() override;
        void Tick() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
