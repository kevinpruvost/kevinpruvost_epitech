#pragma once

// SFML includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// C++ includes
#include <list>
#include <fstream>
#include <map>

namespace RType
{
namespace Common
{
namespace Engine
{
namespace Rendering
{
    enum class RenderingDrawableType : unsigned char
    {
        NoDrawable,
        Sprite,
        Text
    };

    class RenderingDrawable
    {
    public:
        RenderingDrawable()
            : type { RenderingDrawableType::NoDrawable }
        {

        }
        RenderingDrawable(std::shared_ptr<sf::Sprite> nsprite)
            : type { RenderingDrawableType::Sprite }
            , sprite { nsprite }
        {
        }
        RenderingDrawable(std::shared_ptr<sf::Text> ntext)
            : type { RenderingDrawableType::Text }
            , text { ntext }
        {
        }

        sf::Drawable& get()
        {
            switch (type)
            {
            case RenderingDrawableType::Sprite:
                return *sprite;
            case RenderingDrawableType::Text:
                return *text;
            default:
                throw CRITICAL_EXCEPTION("Drawable Error.");
            }
        }

    public:
        RenderingDrawableType type;

            std::shared_ptr<sf::Sprite> sprite;
            std::shared_ptr<sf::Text> text;
    };

    /**
     * @brief Example System class.
     */
    class DrawableContainer : public std::map<EntityId, RenderingDrawable>
    {
    public:
        using std::map<EntityId, RenderingDrawable>::map;
        ~DrawableContainer() {}

        /*template<typename T, class ... Args>
        std::shared_ptr<T> CreateNewDrawable(EntityId entityId, Args && ... args)
        {
            if (!std::is_base_of<sf::Drawable, T>::value)
                throw CRITICAL_EXCEPTION("Trying to create drawable that does not inherits from sf::Drawable : " + typeid(T).name());
        
            auto newDrawable = std::make_shared<RenderingDrawable>(T(std::forward<Args>(args)...));
            insert({ entityId, newDrawable });
            return newDrawable;
        }*/
    };
}; // !RType::Common::Engine::RenderingSystem
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
