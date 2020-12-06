/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Bullet
*/

#include "Bullet.hpp"

using namespace RType::Common::Engine;

Bullet::Bullet(REngine & engine)
    : Particle(engine)
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
    AddComponent<RectangleCollider>();
    AddComponent<Transform>();
    AddComponent<Audio>();

    auto & transform = GetComponent<Transform>();

    transform.isStatic = false;

    transform.vector.size.x = 10;
    transform.vector.size.y = 10;

    transform.vector.position = vec.position;
    transform.vector.position.x += vec.size.x * (ally == true ? 1 : -1);

    transform.vector.MoveTo(ally ? 1980 : 0, vec.position.y, 300);

    GetComponent<Audio>().audioName = "hit";

    GetComponent<RectangleCollider>().colliderLayer = ColliderLayer::Player;
    GetComponent<RectangleCollider>().callbackOnCollision = [=](const Collider & othercollider) {
        auto othercolliderLayer = othercollider.colliderLayer;

        GetComponent<Audio>().isPlaying = true;

        switch (othercolliderLayer) {
            case Engine::ColliderLayer::Enemy:
                othercollider.GetComponent<CharacterCharacteristics>()._currentHealth -= _damage;
                break;
            default:
                break;
        }

        _engine.get().DestroyEntityId(_id);
    };
}