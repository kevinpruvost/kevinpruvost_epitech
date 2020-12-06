/*
** EPITECH PROJECT, 2020
** Sdl.cpp
** File description:
** sfml
*/

#include "Sdl.hpp"

// C++ includes
#include <iostream>
#include <chrono>

Sdl::Sdl(ArcadeContent & arcadeContent)
    : ADisplayModule(arcadeContent, "SDL")
    , _window { nullptr }
    , _renderer { nullptr }
{
    _oldMap.clear();
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        _oldMap.push_back(std::vector<char>());
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            _oldMap[i].push_back(0);
        }
    }

    SDL_Init(SDL_INIT_VIDEO);

	_window = NULL;
	_window = SDL_CreateWindow("Arcade Machine - SDL Display Mode",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		static_cast<int>(WINDOW_X),
		static_cast<int>(WINDOW_Y),
		SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_window) {
		throw EXCEPTION("Cant create Window");
		return;
	}
}

Sdl::~Sdl()
{
    for (auto & pair : _textureMap)
        SDL_DestroyTexture(pair.second);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Sdl::updateEvent()
{
    static auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();

	SDL_Event event;

    if (SDL_PollEvent(&event))
        if (event.type == SDL_QUIT)
        {
            setKey(ArcadeEvent::KeyValue::EXIT);
            return;
        }

    if (event.type == SDL_KEYDOWN && elapsed_seconds >= 200)
    {
        if (IS_KEY_PRESSED(SDLK_x))
            setKey(ArcadeEvent::KeyValue::EXIT); // Left Shift + Q : Quit
        else if (IS_KEY_PRESSED(SDLK_LEFT) || IS_KEY_PRESSED(SDLK_q))
            setKey(ArcadeEvent::KeyValue::LEFT);
        else if (IS_KEY_PRESSED(SDLK_RIGHT) || IS_KEY_PRESSED(SDLK_d))
            setKey(ArcadeEvent::KeyValue::RIGHT);
        else if (IS_KEY_PRESSED(SDLK_UP) || IS_KEY_PRESSED(SDLK_z))
            setKey(ArcadeEvent::KeyValue::UP);
        else if (IS_KEY_PRESSED(SDLK_DOWN) || IS_KEY_PRESSED(SDLK_s))
            setKey(ArcadeEvent::KeyValue::DOWN);
        else if (IS_KEY_PRESSED(SDLK_ESCAPE))
            setKey(ArcadeEvent::KeyValue::ESCAPE);
        else if (IS_KEY_PRESSED(SDLK_RETURN) || IS_KEY_PRESSED(SDLK_SPACE))
            setKey(ArcadeEvent::KeyValue::ENTER);
        else if (IS_KEY_PRESSED(SDLK_m))
            setKey(ArcadeEvent::KeyValue::MAINMENU);
        else if (IS_KEY_PRESSED(SDLK_1))
            changePrevGraphical();
        else if (IS_KEY_PRESSED(SDLK_2))
            changeNextGraphical();
        else if (IS_KEY_PRESSED(SDLK_3))
            changePrevGame();
        else if (IS_KEY_PRESSED(SDLK_4))
            changeNextGame();
        start = std::chrono::system_clock::now();
    }
}

void Sdl::display()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

    int wid = 0;
    int hei = 0;

    for (int i = 0; i < MAP_WIDTH; ++i, wid += SPRITE_WIDTH)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j, hei += SPRITE_HEIGHT)
        {
            if (arcadeMap()[i][j] != 0)
            {
                SDL_Rect rect = {wid, hei, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT};
                SDL_Rect & dstRect = _spriteData[arcadeMap()[i][j]];
                SDL_RenderCopy(_renderer, _textureMap[arcadeMap()[i][j]],
                               &dstRect, &rect);
            }
            _oldMap[i][j] = arcadeMap()[i][j];
        }
        hei = 0;
    }

	SDL_RenderPresent(_renderer);
}

void Sdl::setExtraTexture()
{
    int wid = SPRITE_WIDTH;
    int hei = SPRITE_HEIGHT;

    _textureMap.clear();
    _spriteData.clear();

    for (const auto & pair : _spriteInfos)
    {
        const auto & spriteData = pair.second;

        SDL_Surface * image = IMG_Load(spriteData.spritePictureFilename.c_str());
        if (!image)
        {
            throw EXCEPTION("SDL Exception : Texture '" + spriteData.spritePictureFilename
                + "' cannot be loaded.");
            return;
        }

        SDL_Texture * texture = SDL_CreateTextureFromSurface(_renderer, image);  //La texture monImage contient maintenant l'image importée

        if (texture == NULL)
        {
            throw EXCEPTION("SDL Exception : Texture '" + spriteData.spritePictureFilename
                + "' cannot be loaded.");
            return;
        }

        _textureMap.insert(std::make_pair(spriteData.character, texture));
        _spriteData.insert(std::make_pair(spriteData.character, (SDL_Rect)
            { (int)spriteData.spriteLeft,  (int)spriteData.spriteTop,
              (int)spriteData.spriteWidth, (int)spriteData.spriteHeight }));
        
        SDL_QueryTexture(texture, NULL, NULL, &wid, &hei);
    }
}