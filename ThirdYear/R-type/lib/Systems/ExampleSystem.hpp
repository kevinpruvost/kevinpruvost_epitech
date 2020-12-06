#pragma once

#include "Engine/RSystem.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Example System class.
     */
    class ExampleSystem : virtual public RSystem
    {
    public:
        ExampleSystem(REngine & engine);
        ~ExampleSystem();

        void Start() override;
        void Update() override;
        void Tick() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
