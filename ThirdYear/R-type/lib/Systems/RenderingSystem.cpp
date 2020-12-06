#include "RenderingSystem.hpp"

using namespace RType::Common::Engine;

RenderingSystem::RenderingSystem(REngine& engine)
    : RSystem(engine)
{
    std::ifstream ifs(Constants::resourcesPathsFilePath);
    _resourcesPathsFile = nlohmann::json::parse(ifs);
    if (_resourcesPathsFile == nlohmann::json::value_t::discarded)
    {
        throw CRITICAL_EXCEPTION("'" + Constants::resourcesPathsFilePath
            + "' missing or not well formated.");
    }

    _window.setActive(false);
}

RenderingSystem::~RenderingSystem()
{
    if (_window.isOpen())
        _window.close();
    _window.setActive(false);
}

void RenderingSystem::Start()
{
    // Component Signatures.
    AddComponentSignature<Engine::SpriteAnimation>();
    AddComponentSignature<Engine::Sprite>();
    AddComponentSignature<Engine::Text>();
    AddComponentSignature<Engine::KeyInput>();
    AddComponentSignature<Engine::Audio>();

    // Loading window.
    _videoMode = sf::VideoMode::getDesktopMode();
    _window.create(_videoMode, "R-Type", sf::Style::Default | sf::Style::Fullscreen);

    // Checks if the actual thread is the main thread.
    if (std::this_thread::get_id() != _engine.get().mainThreadId)
        _window.setActive(true);

    // Start chronometer.
    _chronometer.start();

    // Loading sprites, fonts and musics.
    if (_resourcesPathsFile["sprites"].is_null() || !_resourcesPathsFile["sprites"].is_object())
        throw CRITICAL_EXCEPTION("Json 'sprites' object missing.");

    if (_resourcesPathsFile["fonts"].is_null() || !_resourcesPathsFile["fonts"].is_object())
        throw CRITICAL_EXCEPTION("Json 'fonts' object missing.");

    if (_resourcesPathsFile["sounds"].is_null() || !_resourcesPathsFile["sounds"].is_object())
        throw CRITICAL_EXCEPTION("Json 'sounds' object missing.");

    DEBUG_LOG("Begin resources loading...");

    {
        auto items = _resourcesPathsFile["sprites"].items();
        auto end = _resourcesPathsFile["sprites"].items().end();
        for (auto ite = _resourcesPathsFile["sprites"].items().begin(); ite != end; ++ite)
        {
            auto spriteNames = ite.value().get<std::vector<std::string>>();

            if (spriteNames.empty())
                throw CRITICAL_EXCEPTION("Json sprite array not well formated at key : " + ite.key());

            _textures.insert({ ite.key(), std::vector<sf::Texture>() });
            _sprites.insert({ ite.key(), std::vector<sf::Sprite>() });
            for (auto& path : spriteNames)
            {
                sf::Texture newTexture;
                if (!newTexture.loadFromFile(path))
                    throw CRITICAL_EXCEPTION("Couldn't load texture : " + ite.key() + " : " + path);
                sf::Sprite newSprite;
                newSprite.setTexture(newTexture);
                _textures[ite.key()].push_back(newTexture);
                _sprites[ite.key()].push_back(newSprite);
                LOG_INFO("'" << path << "' sprite has been loaded.");
            }
            LOG_INFO("'" << ite.key() << "' sprite pack has been loaded.");
        }
    }

    {
        auto items = _resourcesPathsFile["fonts"].items();
        auto end = _resourcesPathsFile["fonts"].items().end();
        for (auto ite = _resourcesPathsFile["fonts"].items().begin(); ite != end; ++ite)
        {
            sf::Font newFont;
            newFont.loadFromFile(ite.value());
            _fonts.insert({ ite.key(), newFont });
            LOG_INFO("'" << ite.key() << "' font has been loaded.");
        }
    }

    {
        auto items = _resourcesPathsFile["sounds"].items();
        auto end = _resourcesPathsFile["sounds"].items().end();
        for (auto ite = _resourcesPathsFile["sounds"].items().begin(); ite != end; ++ite)
        {
            sf::SoundBuffer newBuffer;
            newBuffer.loadFromFile(ite.value());
            sf::Sound newSound;
            newSound.setBuffer(newBuffer);
            _soundBuffers.insert({ ite.key(), newBuffer });
            _sounds.insert({ ite.key(), newSound });
            LOG_INFO("'" << ite.key() << "' sound has been loaded.");
        }
    }

    // Loading icon.
    sf::Image icon = _textures.at("icon")[0].copyToImage();
    _window.setIcon(64, 64, icon.getPixelsPtr());

    // Loading font.
    _defaultFont = _fonts["default_font"];

}

void RenderingSystem::Update()
{
    if (!_window.isOpen())
    {
        _engine.get().Stop(true);
        return;
    }

    while (_window.pollEvent(_event))
    {
        ManageEvents();
    }

    _window.clear(Constants::spaceColor);

    Draw();

    _window.display();

    ++framesDisplayed;
}

void RenderingSystem::Draw()
{
    for (int i = 0; i < _entities.size(); ++i)
    {
        auto ite = _entities.begin();
        std::advance(ite, i);
        auto& entity = ite->second;

        if (!entity->started)
            continue;

        if (entity->HasComponent<Sprite>())
            ManageSprite(entity);
        else if (entity->HasComponent<Text>())
            ManageText(entity);

        if (entity->HasComponent<Audio>())
            ManageSound(entity);
    }

    for (auto& drawable : _drawableContainer)
        _window.draw(drawable.second.get());

    for (auto& drawable : _uiDrawableContainer)
        _window.draw(drawable.second.get());
}

void RenderingSystem::ManageSprite(const std::shared_ptr<REntity>& entity)
{
    // Giving space to new entity sprite.
    if (_drawableContainer.find(entity->getId()) == _drawableContainer.end()
        && _uiDrawableContainer.find(entity->getId()) == _uiDrawableContainer.end())
    {
        auto& spriteComponent = entity->GetComponent<Sprite>();
        const auto& spriteName = spriteComponent.spriteName;

        if (_sprites.find(spriteName) == _sprites.end())
            throw CRITICAL_EXCEPTION("Sprite has a non existent sprite name in the resources json : " + spriteName);

        auto newSprite = std::make_shared<sf::Sprite>(_sprites.at(spriteName)[0]);
        newSprite->setTexture(_textures.at(spriteName)[0]);
        newSprite->setColor(spriteColorToSfColor(spriteComponent.color));
        Rendering::RenderingDrawable container(newSprite);

        if (entity->HasComponent<UITransform>())
        {
            _uiDrawableContainer[entity->getId()] = container;
        }
        else if (entity->HasComponent<Transform>())
        {
            _drawableContainer[entity->getId()] = container;
        }
        else
        {
            throw CRITICAL_EXCEPTION("Drawable has no transform component.");
        }

        if (entity->HasComponent<SpriteAnimation>())
        {
            entity->GetComponent<SpriteAnimation>().startChrono();
        }
    }

    // Updating entity sprite.
    if (_drawableContainer.find(entity->getId()) != _drawableContainer.end())
    {
        auto vector = entity->GetComponent<Transform>().vector;
        auto & sprite = _drawableContainer[entity->getId()].sprite;
        sprite->setPosition(vector.position.x, vector.position.y);
        sf::Vector2u scale = sprite->getTexture()->getSize();
        sf::Vector2f finalSize = { vector.size.x, vector.size.y };
        finalSize.x = scale.x / finalSize.x;
        finalSize.y = scale.y / finalSize.y;
        sprite->setScale(finalSize);

        if (entity->HasComponent<SpriteAnimation>())
        {
            auto& spriteAnimation = entity->GetComponent<SpriteAnimation>();
            auto& spriteComponent = entity->GetComponent<Sprite>();

            if (spriteAnimation.animationLooped)
            {
                if (spriteAnimation.getChronoTime() >= spriteAnimation.animationRate)
                {
                    ++spriteAnimation.animationIndex;
                    if (spriteAnimation.animationIndex >= _textures[spriteComponent.spriteName].size())
                        spriteAnimation.animationIndex = 0;
                    sprite->setTexture(_textures[spriteComponent.spriteName][spriteAnimation.animationIndex]);
                    spriteAnimation.startChrono();
                }
            }
            else
            {
                sprite->setTexture(_textures[spriteComponent.spriteName][0]);
            }
        }
    }
    else if (_uiDrawableContainer.find(entity->getId()) != _uiDrawableContainer.end())
    {
        auto& uitransform = entity->GetComponent<UITransform>();
        auto sprite = _uiDrawableContainer[entity->getId()].sprite;
        sprite->setPosition(uitransform.position.x * WINDOW_WIDTH,
                            uitransform.position.y * WINDOW_HEIGHT);
        sf::Vector2u scale = sprite->getTexture()->getSize();
        sf::Vector2f finalSize = { WINDOW_WIDTH * uitransform.size.x, WINDOW_HEIGHT * uitransform.size.y };
        finalSize.x = finalSize.x / scale.x;
        finalSize.y = finalSize.y / scale.y;
        sprite->setScale(finalSize);
        if (uitransform.centered)
        {
            sprite->setOrigin((float)sprite->getTexture()->getSize().x / 2,
                              (float)sprite->getTexture()->getSize().y / 2);
        }
        else
            sprite->setOrigin(0, 0);

        if (entity->HasComponent<SpriteAnimation>())
        {
            auto& spriteAnimation = entity->GetComponent<SpriteAnimation>();
            auto& spriteComponent = entity->GetComponent<Sprite>();

            if (spriteAnimation.animationLooped)
            {
                if (spriteAnimation.getChronoTime() >= spriteAnimation.animationRate)
                {
                    ++spriteAnimation.animationIndex;
                    if (spriteAnimation.animationIndex >= _textures[spriteComponent.spriteName].size())
                        spriteAnimation.animationIndex = 0;
                    sprite->setTexture(_textures[spriteComponent.spriteName][spriteAnimation.animationIndex]);
                    spriteAnimation.startChrono();
                }
            }
            else
            {
                sprite->setTexture(_textures[spriteComponent.spriteName][0]);
            }
        }
    }
}

void RenderingSystem::ManageText(const std::shared_ptr<REntity>& entity)
{
    // Giving space to new entity sprite.
    if (_drawableContainer.find(entity->getId()) == _drawableContainer.end()
        && _uiDrawableContainer.find(entity->getId()) == _uiDrawableContainer.end())
    {
        const auto& txt = entity->GetComponent<Text>();

        if (_fonts.find(txt.fontName) == _fonts.end())
            throw CRITICAL_EXCEPTION("Font has a non existent font name in the resources json.");

        auto newText = std::make_shared<sf::Text>(txt.text, _fonts.at(txt.fontName), txt.fontSize);
        Rendering::RenderingDrawable container(newText);

        if (entity->HasComponent<UITransform>())
        {
            _uiDrawableContainer[entity->getId()] = container;
        }
        else if (entity->HasComponent<Transform>())
        {
            _drawableContainer[entity->getId()] = container;
        }
        else
        {
            throw CRITICAL_EXCEPTION("Drawable has no transform component.");
        }
    }

    // Updating entity sprite.
    if (_drawableContainer.find(entity->getId()) != _drawableContainer.end())
    {
        auto vector = entity->GetComponent<Transform>().vector;
        auto& txt = entity->GetComponent<Text>();
        auto& text = _drawableContainer[entity->getId()].text;
        text->setPosition(vector.position.x, vector.position.y);
        text->setString(txt.text);
        text->setCharacterSize(txt.fontSize);
        if (_fonts.find(txt.fontName) != _fonts.end())
            text->setFont(_fonts[txt.fontName]);
        text->setFillColor(fontColorToSfColor(txt.fontColor));
    }
    else if (_uiDrawableContainer.find(entity->getId()) != _uiDrawableContainer.end())
    {
        auto& uitransform = entity->GetComponent<UITransform>();
        auto & txt = entity->GetComponent<Text>();
        auto text = _uiDrawableContainer[entity->getId()].text;
        text->setPosition(uitransform.position.x * WINDOW_WIDTH,
            uitransform.position.y * WINDOW_HEIGHT);
        if (_fonts.find(txt.fontName) != _fonts.end())
            text->setFont(_fonts[txt.fontName]);
        text->setString(txt.text);
        text->setCharacterSize(txt.fontSize);
        text->setFillColor(fontColorToSfColor(txt.fontColor));
    }
}

void RenderingSystem::ManageKeyInput(const std::shared_ptr<REntity>& entity)
{
    auto& keyInput = entity->GetComponent<KeyInput>();
    if (_event.type == sf::Event::KeyPressed)
    {
        if (keyInput.inputCodes[(int)_event.key.code])
        {
            keyInput.pressed = true;
            keyInput.inputCode = (Rfc::InputCode)_event.key.code;
        }
    }
    else if (_event.type == sf::Event::KeyReleased)
    {
        if (keyInput.inputCodes[(int)_event.key.code])
            keyInput.pressed = false;
    }
}

void RenderingSystem::ManageSound(const std::shared_ptr<REntity>& entity)
{
    auto& soundComponent = entity->GetComponent<Audio>();
    if (_soundContainer.find(entity->getId()) == _soundContainer.end())
    {
        if (_sounds.find(soundComponent.audioName) == _sounds.end())
            throw CRITICAL_EXCEPTION("Trying to get sound file that does not exist : " + soundComponent.audioName);
        _soundContainer.insert({ entity->getId(), _sounds.at(soundComponent.audioName)});
        _soundContainer[entity->getId()].setBuffer(_soundBuffers.at(soundComponent.audioName));
    }
    auto & sound = _soundContainer[entity->getId()];
    
    sound.setVolume(soundComponent.volume);
    sound.setPitch(soundComponent.pitch);
    sound.setLoop(soundComponent.isLooped);
    if (sound.getStatus() != sf::Sound::Status::Playing && soundComponent.isPlaying)
    {
        sound.play();
        if (!soundComponent.isLooped)
            soundComponent.isPlaying = false;
    }
    if (sound.getStatus() == sf::Sound::Status::Playing && soundComponent.isStoped)
        sound.stop();
    if (soundComponent.isPaused)
        sound.pause();
}

void RenderingSystem::Tick()
{
}

void RenderingSystem::OnEntityDestruction(EntityId id)
{
    DEBUG_LOG("Destroying in rendering system : " << id);
    if (_drawableContainer.find(id) != _drawableContainer.end())
        _drawableContainer.erase(id);
    if (_uiDrawableContainer.find(id) != _uiDrawableContainer.end())
        _uiDrawableContainer.erase(id);
    if (_soundContainer.find(id) != _soundContainer.end())
        _soundContainer.erase(id);
}

void RenderingSystem::ManageEvents()
{
    if (_event.type == sf::Event::Closed)
    {
        _window.close();
    }

    for (int i = 0; i < _entities.size(); ++i)
    {
        auto ite = _entities.begin();
        std::advance(ite, i);
        auto& entity = ite->second;

        if (!entity->started)
            continue;

        if (entity->HasComponent<KeyInput>())
            ManageKeyInput(entity);
    }
}

double RenderingSystem::getFps()
{
    _fps = (double)framesDisplayed / _chronometer.getPastTimeInSeconds();
    return _fps;
}

sf::Color RenderingSystem::fontColorToSfColor(FontColor color)
{
    sf::Color newColor;
    newColor.r = color.r;
    newColor.g = color.g;
    newColor.b = color.b;
    newColor.a = color.a;
    return newColor;
}

sf::Color RenderingSystem::spriteColorToSfColor(SpriteColor color)
{
    sf::Color newColor;
    newColor.r = color.r;
    newColor.g = color.g;
    newColor.b = color.b;
    newColor.a = color.a;
    return newColor;
}

sf::Keyboard::Key RenderingSystem::RTypeKeyToSfmlKey(Rfc::InputCode inputCode)
{
    return (sf::Keyboard::Key)inputCode;
}
