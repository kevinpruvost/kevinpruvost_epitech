/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InGameGenericMob
*/

#include "InGameGenericMob.hpp"

using namespace RType::Common::Engine;

InGameGenericMob::InGameGenericMob(REngine & engine)
    : Enemy(engine)
{
}

InGameGenericMob::~InGameGenericMob()
{
}

void InGameGenericMob::Start()
{
    Enemy::Start();

    auto & audio = GetComponent<Audio>();

    auto & transform = GetComponent<Transform>();

    transform.vector.position.x = rand() % 50 + 1980;
    transform.vector.position.y = rand() % 600 + 200;

    int random = rand() % 50 + 100;
    transform.vector.size.x = random;
    transform.vector.size.y = random;
    transform.isStatic = false;

    transform.vector.MoveTo(0, transform.vector.position.y, 150);

    auto & character = GetComponent<CharacterCharacteristics>();

    character._currentHealth = 50;
    character._maxHealth = 50;

    std::array<std::string, 4> death = {"death1", "death2", "death3", "death4"};
    std::array<std::string, 2> sprite = {"enemy1", "enemy2"};
    std::array<std::string, 2> bulletsprite = {"enemy_projectile1", "enemy_projectile2"};

    GetComponent<Sprite>().spriteName = sprite[rand() % 2];
    audio.audioName = death[rand() % 4];

    GetComponent<Weapon>().ally = false;
    GetComponent<Weapon>().spriteNameBullet = bulletsprite[rand() % 2];

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

    LOG_INFO("Mob : " << getId() << " " << transform.entityId);

}

void InGameGenericMob::Update()
{
    auto & character = GetComponent<CharacterCharacteristics>();

    if (character._currentHealth <= 0) {
        _engine.get().DestroyEntityId(_id);
    }
}