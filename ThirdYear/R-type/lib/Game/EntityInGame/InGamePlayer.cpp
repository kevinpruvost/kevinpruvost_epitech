/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Player
*/

#include "InGamePlayer.hpp"

using namespace RType::Common::Engine;

InGamePlayer::InGamePlayer(REngine & engine)
    : Player (engine)
{
}

InGamePlayer::~InGamePlayer()
{
}

void InGamePlayer::Start()
{
    Player::Start();

    AddComponent<SpriteAnimation>();

    GetComponent<Sprite>().spriteName = "player";

    auto & characteristics = GetComponent<CharacterCharacteristics>();
    characteristics.setCurrentHealth(100);
    characteristics.setMaxHealth(100);
    characteristics.setSpeed(1.f);

    auto & transform = GetComponent<Transform>();
    transform.vector.position.x = 400;
    transform.vector.position.y = 500;
    transform.vector.size.x = 200;
    transform.vector.size.y = 200;

    auto & audio = GetComponent<Audio>();
    audio.audioName = "shot";
    audio.isPlaying = false;
    audio.isLooped = false;

    GetComponent<Weapon>().spriteNameBullet = "player_projectile";
    GetComponent<Weapon>().ally = true;

    GetComponent<RectangleCollider>().colliderLayer = Engine::ColliderLayer::Player;
    GetComponent<RectangleCollider>().callbackOnCollision = [=](const Collider & othercollider) {
        auto othercolliderLayer = othercollider.colliderLayer;

        switch (othercolliderLayer) {
            case Engine::ColliderLayer::Player:
                break;
            case Engine::ColliderLayer::Enemy:
                GetComponent<CharacterCharacteristics>()._currentHealth = 0;
                break;
            case Engine::ColliderLayer::Obstacle:
                GetComponent<CircleCollider>().FixPosition(othercollider);
                break;
            case Engine::ColliderLayer::NoLayer:
                GetComponent<CircleCollider>().FixPosition(othercollider);
                break;
            default:
                break;
        }
    };
}

void InGamePlayer::Update()
{
    auto & character = GetComponent<CharacterCharacteristics>();

    if (character._currentHealth <= 0) {
        _engine.get().DestroyEntityId(_id);
    }
}

void InGamePlayer::ChangeColorSprite(SpriteColor spritecolor)
{
    GetComponent<Sprite>().color = spritecolor;
}


void InGamePlayer::Input(Rfc::InputCode key)
{
    switch (key)
    {
    case Rfc::InputCode::Left:
        MoveToLeft();
        break;
    case Rfc::InputCode::Right:
        MoveToRight();
        break;
    case Rfc::InputCode::Down:
        MoveDown();
        break;
    case Rfc::InputCode::Up:
        MoveUp();
        break;
    case Rfc::InputCode::Space:
        Shoot();
        break;
    default:
        break;
    }
}

void InGamePlayer::MoveToLeft()
{
    auto & transform = GetComponent<Transform>();
    transform.vector.MoveTo(0, transform.vector.position.y, transform.vector.GetSpeed());
}

void InGamePlayer::MoveToRight()
{
    auto & transform = GetComponent<Transform>();
    transform.vector.MoveTo(1980, transform.vector.position.y, transform.vector.GetSpeed());
}

void InGamePlayer::MoveDown()
{
    auto & transform = GetComponent<Transform>();
    transform.vector.MoveTo(transform.vector.position.x, 1080, transform.vector.GetSpeed());
}

void InGamePlayer::MoveUp()
{
    auto & transform = GetComponent<Transform>();
    transform.vector.MoveTo(transform.vector.position.x, 0, transform.vector.GetSpeed());
}

void InGamePlayer::Shoot()
{
    GetComponent<Audio>().isPlaying = true;
    createBullet();
}