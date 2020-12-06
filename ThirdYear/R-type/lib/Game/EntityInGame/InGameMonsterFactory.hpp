/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InGameMonsterFactory
*/

#pragma once

#include "Entities/Object/Character/NonPlayerCharacter/Enemy/Enemy.hpp"
#include "Chronometer.hpp"
#include "Exception.hpp"
#include "InGameBoss.hpp"
#include "InGameGenericMob.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class InGameMonsterFactory : public REntity {

        RENTITY_MANDATORIES(InGameMonsterFactory)

        public:
            InGameMonsterFactory(REngine & engine);
            ~InGameMonsterFactory();

            void Start() override;
            void Update() override;

            void AddNewEnemy(const std::string & enemy);

        private:
            Chronometer chrono;
            Chronometer boosChrono;
            std::vector<std::string> enemyToSpawn;
            std::string boosName;
    };
};
};
};
