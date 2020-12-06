#pragma once

#include "Network/Rfc.hpp"

#include <string>

namespace RType
{
namespace Common
{
namespace Engine
{
    enum class ColliderType : unsigned char
    {
        Rectangle = 0,
        Circle
    };

    enum class ColliderLayer : unsigned char
    {
        NoLayer = 0,
        Player,
        Enemy,
        Obstacle,
        Pickable
    };

    struct SpriteColor
    {
        unsigned char r = 255;
        unsigned char g = 255;
        unsigned char b = 255;
        unsigned char a = 255;
    };

    enum class AnimationBoucle {
        DontStop,
        StopAtFirstFrame,
        StopAtLastFrame
    };

    enum class AnimationDirection : char {
        ToRight,
        ToLeft
    };

    struct FontColor
    {
        unsigned char r = 255;
        unsigned char g = 255;
        unsigned char b = 255;
        unsigned char a = 255;
    };

    using ComponentId = unsigned int;
    using ComponentSignature = short unsigned int;

    /**
     * @brief Component Interface.
     */
    class IComponent
    {
        public:
            virtual ~IComponent() = default;

            /**
             * @brief Pure function used by the REngine.
             * Its purpose is to be overriden by the children classes, mainly by RComponent direct children.
             */
            virtual void Update() = 0;
            /**
             * @brief Pure function used by the REngine, launched on every turn of the game loop.
             * Its purpose is to be overriden by RComponent, UpdateEngine() will mainly call Update() and do some other corrections
             */
            virtual void UpdateEngine() = 0;
            /**
             * @brief Pure function used by the REngine, launched at the first frame where the object is created
             */
            virtual void Start() = 0;
            /**
             * @brief Pure function used by the REngine, launched at each tick of the game loop.
             */
            virtual void Tick() = 0;

            virtual std::string ClassName() = 0;

            virtual Rfc::ComponentTypeId GetComponentTypeId() = 0;

            virtual size_t GetComponentSize() = 0;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
