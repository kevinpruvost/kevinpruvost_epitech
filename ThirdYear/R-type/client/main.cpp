/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

// Project includes
#include "Client.hpp"

#include "DebugController.hpp"
#include "Systems/ColliderSystem.hpp"
#include "Systems/RenderingSystem.hpp"
#include "Systems/MovementSystem.hpp"
#include "../tests/Engine/ColliderTest.hpp"

#include "Game/TitleScreen.hpp"
#include "Game/FpsDisplayer.hpp"
#include "Game/MenuPage/TextBar.hpp"
#include "Game/MenuPage/Background.hpp"
#include "Game/MenuPage/MenuAudio.hpp"
#include "Game/MenuPage/TextBarImage.hpp"
#include "Game/MenuPage/TextRoom.hpp"
//game
#include "Game/EntityInGame/Lib.hpp"

#include "Client.hpp"

using namespace RType::Common;

int main(int argc, const char ** argv)
{
    DebugController::debugArgsIdentify(argc, argv);

    try
    {
        Engine::REngine engine;
        boost::asio::io_context context;
        Client::Client c(context, "127.0.0.1", 7171);

        engine.RegisterComponent<Engine::Audio>(Rfc::ComponentTypeId::Audio);
        engine.RegisterComponent<Engine::KeyInput>(Rfc::ComponentTypeId::KeyInput);
        engine.RegisterComponent<Engine::Transform>(Rfc::ComponentTypeId::Transform);
        engine.RegisterComponent<Engine::UITransform>(Rfc::ComponentTypeId::UITransform);
        engine.RegisterComponent<Engine::RectangleCollider>(Rfc::ComponentTypeId::RectangleCollider);
        engine.RegisterComponent<Engine::CircleCollider>(Rfc::ComponentTypeId::CircleCollider);
        engine.RegisterComponent<Engine::SpriteAnimation>(Rfc::ComponentTypeId::SpriteAnimation);
        engine.RegisterComponent<Engine::Sprite>(Rfc::ComponentTypeId::Sprite);
        engine.RegisterComponent<Engine::Text>(Rfc::ComponentTypeId::Text);
        engine.RegisterComponent<Engine::TextInput>(Rfc::ComponentTypeId::TextInput);
        engine.RegisterComponent<Engine::CharacterCharacteristics>(Rfc::ComponentTypeId::CharacterCharacteristics);
        engine.RegisterComponent<Engine::Weapon>(Rfc::ComponentTypeId::Weapon);

        auto colliderSystem = engine.RegisterSystem<Engine::ColliderSystem>(engine);
        auto movementSystem = engine.RegisterSystem<Engine::MovementSystem>(engine);
        auto renderSystem = engine.RegisterSystem<Engine::RenderingSystem>(engine);

        auto background = engine.CreateEntity<Engine::Background>(engine);
        auto title = engine.CreateEntity<Engine::TitleScreen>(engine);
        //auto fps = engine.CreateEntity<Engine::FpsDisplayer>(engine);
        auto barimage = engine.CreateEntity<Engine::TextBarImage>(engine);
        auto textbar = engine.CreateEntity<Engine::TextBar>(engine);
        auto textroom = engine.CreateEntity<Engine::TextRoom>(engine);
        auto fpsDisplayer = engine.CreateEntity<Engine::FpsDisplayer>(engine);
        textbar->SetTextBarCallback([&]() {
            const auto& text = textbar->GetComponent<Engine::Text>().text;
            c.sendLogin(text);
        });
        auto music = engine.CreateEntity<Engine::MenuAudio>(engine);

        engine.callbackOnStop = [&]() {
            context.stop();
        };

        c.linkEngine(&engine);
        engine.LoopOnThread();
        context.run();

    } catch (const MinorException & e) {
        LOG_ERROR(e.what());
    } catch (const CriticalException& e) {
        LOG_ERROR(e.what());
    }

    return EXIT_SUCCESS;
}