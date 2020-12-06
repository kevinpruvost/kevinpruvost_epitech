/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InGameMonsterFactory
*/

#include "InGameMonsterFactory.hpp"

using namespace RType::Common::Engine;

InGameMonsterFactory::InGameMonsterFactory(REngine & engine)
    : REntity (engine)
{
}

InGameMonsterFactory::~InGameMonsterFactory()
{
}

void InGameMonsterFactory::Start()
{
    chrono.start();
    boosChrono.start();

    boosName = typeid(InGameBoss).name();

    AddNewEnemy(typeid(InGameGenericMob).name());
}

void InGameMonsterFactory::Update()
{
    if (enemyToSpawn.empty())
        throw CRITICAL_EXCEPTION("No enemy registered in game monster factory");
    if (chrono.getPastTimeInSeconds() >= 2.f) {
        chrono.start();
        _engine.get().CreateEntityFromClassName(enemyToSpawn[rand() % enemyToSpawn.size()]);
    }
    if (boosChrono.getPastTimeInSeconds() >= 30.f) {
        boosChrono.start();
        _engine.get().CreateEntityFromClassName(boosName);
    }
}

void InGameMonsterFactory::AddNewEnemy(const std::string & enemy)
{
    enemyToSpawn.push_back(enemy);
}