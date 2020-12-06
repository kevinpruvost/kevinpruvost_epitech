#pragma once

// Project includes
#include "Engine/RSystem.hpp"

// C++ includes
#include <iostream>

namespace RType
{
namespace Common
{
namespace Engine
{
namespace Test
{
    class TestSystem : public RSystem
    {
    public:
        TestSystem(REngine & engine) : RSystem(engine) { }
        ~TestSystem() { }

        void sayCoom() { std::cout << "Coom !!!" << std::endl; }

        void Start() override final
        {
            std::cout << "Test System started." << std::endl;
        }

        void Update() override final
        {

        }

    public:
    };
}; // !RType::Common::Engine::Test
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
