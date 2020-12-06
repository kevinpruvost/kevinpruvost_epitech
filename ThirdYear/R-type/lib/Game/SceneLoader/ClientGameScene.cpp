#include "SceneLoader.hpp"

using namespace RType::Common::Engine;

void SceneLoader::ClientGameScene()
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
    auto colliderSystem = engine.RegisterSystem<Engine::ColliderSystem>(engine);
    auto renderingSystem = engine.RegisterSystem<Engine::RenderingSystem>(engine);
    auto movementSystem = engine.RegisterSystem<Engine::MovementSystem>(engine);
    auto entity = engine.CreateEntity<Engine::Test::ColliderTest>(engine);
    auto background = engine.CreateEntity<Engine::Background>(engine);
    auto title = engine.CreateEntity<Engine::TitleScreen>(engine);
    auto imagebar = engine.CreateEntity<Engine::TextBarImage>(engine);
    auto textinput = engine.CreateEntity<Engine::TextBar>(engine);
    auto textroom = engine.CreateEntity<Engine::TextRoom>(engine);
    textinput->SetTextBarCallback([&]() {
        const auto& text = textinput->GetComponent<Engine::Text>().text;
        c.sendLogin(text);
    });
    auto fpsDisplayer = engine.CreateEntity<Engine::FpsDisplayer>(engine);
    auto audio = engine.CreateEntity<Engine::MenuAudio>(engine);
    void* data = static_cast<void*>(&(*entity));
    auto reEntity = static_cast<Engine::Test::ColliderTest*>(data);
    engine.RegisterEntity(*reEntity);

    engine.LoopOnThread();
    context.run();
}
