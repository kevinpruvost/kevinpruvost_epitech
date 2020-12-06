#pragma once

// Project includes
#include "Engine/REntity.hpp"
#include "Components/Collider/CircleCollider/CircleCollider.hpp"

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
    class ColliderTest : public REntity
    {
        RENTITY_MANDATORIES(ColliderTest)

    public:
        ColliderTest(REngine & engine) : REntity(engine) { }
        ~ColliderTest() { }

        void Start() override
        {
            DEBUG_LOG("XD BVRDQZDQZDQZD");
            AddComponent<Transform>();
            AddComponent<CircleCollider>();

            auto vec = GetComponent<Transform>().vector;
            vec.size.x = 5;
            vec.size.y = 5;
            GetComponent<Transform>().vector = vec;
        }

        void Update() override
        {
            DEBUG_LOG("La CON");
        }

        void sayCoom() { std::cout << "Coom !!! + " << testVar << std::endl; }

    public:
        int testVar = 0;
    };
}; // !RType::Common::Engine::Test
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
