/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** CharacterCharacteristics
*/

#pragma once

#include "Engine/RComponent.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class CharacterCharacteristics : public RComponent {

        RCOMPONENT_MANDATORIES(CharacterCharacteristics)

        public:
            CharacterCharacteristics(REngine & engine);
            ~CharacterCharacteristics();

            //get
            unsigned int getCurrentHealth() const {return _currentHealth;};
            unsigned int getMaxhealth() const {return _maxHealth;};
            float getSpeed() const {return _speed;};

            //set
            void setCurrentHealth(unsigned int current) {_currentHealth = current;};
            void setMaxHealth(unsigned int max) {_maxHealth = max;}; 
            void setSpeed(float speed) {_speed = speed;}; 

            virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

        public:
            unsigned int _currentHealth = 100;
            unsigned int _maxHealth = 100;
            float _speed = 1.f;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType