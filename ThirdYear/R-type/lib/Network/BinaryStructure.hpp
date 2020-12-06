#pragma once

// Project includes
#include "Rfc.hpp"

#include "Engine/IComponent.hpp"
#include "Engine/IEntity.hpp"

#define ROOM_ID_SIZE 8
#define IP_LENGTH 16
#define USERNAME_LENGTH 32
#define COMPONENT_NAME_LENGTH 64

namespace RType
{
namespace Common
{
    namespace Udp
    {
        struct Header
        {
            Rfc::UdpCode code;
            short unsigned int size;
        };

        /*
        ** Command structs.
        */

        struct ReadyRequest {
            Header header;
        };

        struct GameStartedAnswer {
            Header header;
        };

        struct UsernameRequest
        {
            Header header;
            char username[USERNAME_LENGTH];
        };

        struct InputRequest
        {
            Header header;
            Rfc::InputCode inputCode;
        };

        struct InputXYRequest
        {
            Header header;
            Rfc::InputCode inputCode;
            float inputValue;
            float inputValue2;
        };

        struct LogoutRequest
        {
            Header header;
        };

        struct Error
        {
            Header header;
        };

        namespace Entities
        {
            struct CreateEntity
            {
                Udp::Header header;
                unsigned int id;
            };

            struct AudioComponent {
                char audioName[COMPONENT_NAME_LENGTH];
                bool isPlaying;
                bool isPaused;
                bool isStoped;
                bool isLooped;
                float pitch;
                unsigned short volume;
            };

            struct WeaponComponent {
                float _fireRate;
                float _damage;
                unsigned int _projectileNumber;
                char spriteNameBullet[COMPONENT_NAME_LENGTH];
                bool ally = false;
            };

            struct CharacterCharacteristicsComponent {
                unsigned int _currentHealth;
                unsigned int _maxHealth;
                float _speed;
            };

            struct ColiderComponent {
                RType::Common::Engine::ColliderType colliderType;
                RType::Common::Engine::ColliderLayer colliderLayer;
            };

            struct SpriteAnimationComponent {
                float animationRate;
                bool animationLooped;
                unsigned char animationIndex;
                RType::Common::Engine::AnimationBoucle boucle;
                RType::Common::Engine::AnimationDirection sens;
            };

            struct SpriteComponent {
                char spriteName[COMPONENT_NAME_LENGTH];
                RType::Common::Engine::SpriteColor color;
            };

            struct TextComponent {
                char text[COMPONENT_NAME_LENGTH];
                char fontName[COMPONENT_NAME_LENGTH];
                int fontSize;
                RType::Common::Engine::FontColor fontColor;
            };

            struct TransformComponent {
                float positionX;
                float positionY;
                float sizeX;
                float sizeY;
                float directionX;
                float directionY;
                float speed;
                bool hasMoved;
                bool isStatic;
                RType::Common::Engine::EntityId parentId;
            };

            struct UITransform {
                float positionX;
                float positionY;
                float sizeX;
                float sizeY;
                bool centered;
            };

            struct CreateComponent {
                Udp::Header header;
                unsigned int entityId;
                RType::Common::Rfc::ComponentTypeId type;
                union {
                    AudioComponent audio;
                    WeaponComponent weapon;
                    CharacterCharacteristicsComponent characterisrics;
                    ColiderComponent colider;
                    SpriteAnimationComponent spriteAnimation;
                    SpriteComponent sprite;
                    TextComponent text;
                    TransformComponent transform;
                    UITransform uiTransform;
                };
            };

            struct UpdateRequest
            {
                Udp::Header header;
                unsigned int entityId;
                Rfc::ComponentTypeId typeId;
                union {
                    AudioComponent audio;
                    WeaponComponent weapon;
                    CharacterCharacteristicsComponent characterisrics;
                    ColiderComponent colider;
                    SpriteAnimationComponent spriteAnimation;
                    SpriteComponent sprite;
                    TextComponent text;
                    TransformComponent transform;
                    UITransform uiTransform;
                };
            };

            struct DeleteRequest
            {
                Udp::Header header;
                unsigned int entityId;
            };
        }; // !R_Type::Common::Udp::Entities
    }; // !R_Type::Common::Udp

    namespace Tcp
    {
        struct Header
        {
            Rfc::TcpCode code;
            size_t size;
        };

        /*
        ** Command structs.
        */

        struct UnknownRequest
        {
            Header header;
        };

        struct ErrorRequest
        {
            Header header;
            Rfc::TcpCode commandId;
            char message[64];
        };

        struct LoginRequest
        {
            Header header;
            char roomId[ROOM_ID_SIZE];
        };

        struct LoginOkAnswer
        {
            Header header;
            unsigned short port;
            char roomId[ROOM_ID_SIZE];
        };

        struct LogoutRequest
        {
            Header header;
            char roomId[ROOM_ID_SIZE];
        };

    }; // !R_Type::Common::Tcp

}; // !R_Type::Common
}; // !R_Type