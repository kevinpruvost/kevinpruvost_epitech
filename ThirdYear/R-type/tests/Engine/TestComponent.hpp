#pragma once

// Project includes
#include "Engine/RComponent.hpp"

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
    class TestComponent : public RComponent
    {

        RCOMPONENT_MANDATORIES(TestComponent)
    
    public:
        TestComponent(REngine & engine) : RComponent(engine) { }
        ~TestComponent() { }

        void sayCoom() { std::cout << "Coom !!!" << std::endl; }

    public:
        int testVar = 0;
    };
}; // !RType::Common::Engine::Test
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
