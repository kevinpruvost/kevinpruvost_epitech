#pragma once

// Project includes
#include "Engine/RSystem.hpp"
#include "Chronometer.hpp"

#include "Systems/RenderingSystem/DrawableContainer.hpp"

#include "Components/Audio/Audio.hpp"

#include "Components/Text/Text.hpp"
#include "Components/Sprite/Sprite.hpp"
#include "Components/Sprite/Animation/SpriteAnimation.hpp"

#include "Components/UITransform/UITransform.hpp"
#include "Components/Transform/Transform.hpp"

#include "Components/KeyInput/KeyInput.hpp"

#include <nlohmann/json.hpp>

// SFML includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>

// C++ includes
#include <fstream>

#define WINDOW_WIDTH  _videoMode.width
#define WINDOW_HEIGHT _videoMode.height

namespace RType
{
namespace Common
{
namespace Engine
{
    namespace Constants
    {
        const sf::Color spaceColor(2, 4, 11);

        // Paths are from the project's root.
        constexpr const char * resourcesPathsFilePath = "resources/resources_paths.json";
    
    }; // !RType::Common::Engine::Constants

    /**
     * @brief Example System class.
     */
    class RenderingSystem : virtual public RSystem
    {
    public:
        RenderingSystem(REngine & engine);
        ~RenderingSystem();

        void Start() override;
        void Update() override;
        void Tick() override;
        void OnEntityDestruction(EntityId id) override;

        void Draw();
        void ManageSprite(const std::shared_ptr<REntity> & entity);
        void ManageText(const std::shared_ptr<REntity>& entity);
        void ManageKeyInput(const std::shared_ptr<REntity>& entity);
        void ManageSound(const std::shared_ptr<REntity>& entity);

        void ManageEvents();

        double getFps();

        sf::Color fontColorToSfColor(FontColor color);
        sf::Color spriteColorToSfColor(SpriteColor color);
        sf::Keyboard::Key RTypeKeyToSfmlKey(Rfc::InputCode inputCode);

    public:
        size_t framesDisplayed = 0;

    protected:
        double _fps = 0;
        Chronometer _chronometer;

    protected:
        sf::RenderWindow _window;
        sf::VideoMode _videoMode;
        sf::Event _event;
        sf::Font _defaultFont;

        nlohmann::json _resourcesPathsFile;

        Rendering::DrawableContainer _drawableContainer;
        Rendering::DrawableContainer _uiDrawableContainer;

        std::unordered_map<EntityId, sf::Sound> _soundContainer;

        std::unordered_map<std::string, std::vector<sf::Texture>> _textures;
        std::unordered_map<std::string, std::vector<sf::Sprite>>  _sprites;
        std::unordered_map<std::string, sf::Font>               _fonts;
        std::unordered_map<std::string, sf::SoundBuffer>        _soundBuffers;
        std::unordered_map<std::string, sf::Sound>              _sounds;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
