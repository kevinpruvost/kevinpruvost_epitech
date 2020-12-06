/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InGameBoss
*/

#include "InGameBoss.hpp"

using namespace RType::Common::Engine;

InGameBoss::InGameBoss(REngine & engine)
    : Enemy (engine)
{
}

InGameBoss::~InGameBoss()
{
}

void InGameBoss::Start()
{
    Enemy::Start();

    auto & audio = GetComponent<Audio>();

    auto & transform = GetComponent<Transform>();

    transform.vector.position.x = rand() % 50 + 1980;
    transform.vector.position.y = rand() % 600 + 200;

    int random = rand() % 50 + 300;
    transform.vector.size.x = random;
    transform.vector.size.y = random;
    transform.isStatic = false;

    LOG_INFO("Boss : " << getId() << " " << transform.entityId);

    transform.vector.MoveTo(0, transform.vector.position.y, 50);

    auto & character = GetComponent<CharacterCharacteristics>();

    character._currentHealth = 500;
    character._maxHealth = 500;

    std::array<std::string, 4> array = {"death1", "death2", "death3", "death4"};

    GetComponent<Sprite>().spriteName = "boss";

    audio.audioName = array[rand() % 4];

    GetComponent<Weapon>().ally = false;
    GetComponent<Weapon>().spriteNameBullet = "boss_projectile";

    GetComponent<RectangleCollider>().colliderLayer = Engine::ColliderLayer::Enemy;
    GetComponent<RectangleCollider>().callbackOnCollision = [=](const Collider & othercollider) {
        auto othercolliderLayer = othercollider.colliderLayer;

        switch (othercolliderLayer) {
            case Engine::ColliderLayer::Player:
                othercollider.GetComponent<CharacterCharacteristics>()._currentHealth = 0;
                break;
            case Engine::ColliderLayer::Obstacle:
                GetComponent<CharacterCharacteristics>()._currentHealth = 0;
                break;
            default:
                break;
        }
    };
}

void InGameBoss::Update()
{
    auto & character = GetComponent<CharacterCharacteristics>();

    if (character._currentHealth <= 0) {
        _engine.get().DestroyEntityId(_id);
    }
}