#pragma once

// Project includes
#include "Engine/REntity.hpp"

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
    class TestEntity : virtual public REntity
    {
        RENTITY_MANDATORIES(TestEntity)

    public:
        TestEntity(REngine & engine) : REntity(engine) { }
        ~TestEntity() { }

        void sayCoom() { std::cout << "Coom !!! + " << testVar << std::endl; }

    public:
        int testVar = 0;
    };
}; // !RType::Common::Engine::Test
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
