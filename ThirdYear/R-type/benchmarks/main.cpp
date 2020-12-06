#include "benchmark/benchmark.h"

// Project includes
#include "Engine/REngine.hpp"
#include "Engine/Entity.hpp"

// C++ includes
#include <vector>
#include <memory>
#include <random>
#include <time.h>
#include <set>

using namespace RType;
using namespace Common;

static void BM_StringReference(benchmark::State & state)
{
    std::string x = "hello";
    for (auto _ : state)
        std::string & o = x;
}

static void BM_StringCopy(benchmark::State & state)
{
    std::string x = "hello";
    for (auto _ : state)
        std::string copy(x);
}

static void BM_EntityIdHandling(benchmark::State & state)
{
    for (auto _ : state)
    {
        Engine::REngine rEngine;
        Engine::Entity entities[2];
    }
}

static void BM_EntityIdReattributionHandling(benchmark::State & state)
{
    srand(time(NULL));
    for (auto _ : state)
    {
        Engine::REngine engine;
        std::set<std::unique_ptr<Engine::Entity>> entities;
        size_t entitiesNumber = 1000;

        for (size_t i = 0; i < entitiesNumber; ++i)
            entities.insert(std::make_unique<Engine::Entity>());

        std::vector<Engine::EntityId> randomIdsDestroyed;

        for (size_t i = 0; i < entitiesNumber && i < entities.size(); i += rand() % 4)
        {
            entities.erase(entities.begin());
        }

        std::vector<std::unique_ptr<Engine::Entity>> newEntities;

        for (size_t i = 0; i < randomIdsDestroyed.size(); ++i)
            newEntities.emplace_back(new Engine::Entity);
    }
}

static void BM_REngineOverallPerformanceTest(benchmark::State& state)
{
    for (auto _ : state)
    {
        Engine::REngine engine;
        
        for (int i = 0; i < 150; ++i)
        {
            Engine::Entity entity;
            entity.setId(engine.CreateEntityId());
        }
    }
}

static void BM_BoolTest(benchmark::State& state)
{
    for (auto _ : state)
    {
        Engine::REngine engine;

        if (engine.isStopped());
    }
}

static void BM_BoolTest2(benchmark::State& state)
{
    for (auto _ : state)
    {
        Engine::REngine engine;

        if (engine.__stop);
    }
}

//BENCHMARK(BM_StringReference);
//BENCHMARK(BM_StringCopy);
BENCHMARK(BM_EntityIdHandling);
BENCHMARK(BM_EntityIdReattributionHandling);
BENCHMARK(BM_REngineOverallPerformanceTest);
BENCHMARK(BM_BoolTest);
BENCHMARK(BM_BoolTest2);

BENCHMARK_MAIN();