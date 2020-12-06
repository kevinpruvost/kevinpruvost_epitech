#pragma once

// Project includes
#include "Component.hpp"
#include "IEntity.hpp"

// C++ includes
#include <vector>
#include <memory>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Entity class.
     */
    class Entity : virtual public IEntity
    {
    public:
        Entity();
        Entity(EntityId id);
        ~Entity();

        virtual void Start() override;
        virtual void Update() override;
        virtual void Tick() override;
        virtual void UpdateEngine() override;

        bool operator==(const Entity& entity)
        {
            return _id == entity._id;
        }

        /**
         * @brief Gets the entity id.
         * 
         * \return 
         */
        EntityId getId() const;
        /**
         * @brief Sets the entity id.
         * 
         * \param id
         */
        void setId(const EntityId id);

        /**
         * Gets the class name. Its main purpose is for derived classes.
         * 
         * \return 
         */
        std::string ClassName() override;

        virtual Entity * ProperCopy() const { return new Entity(*this); }
        virtual Entity * ProperCopy(EntityId id) const { return new Entity(id); }

    public:
        bool started = false;
        const static EntityId EntityIdNull = UINT32_MAX;

    protected:
        EntityId _id;
        std::vector<std::shared_ptr<Component>> _components;

        std::string _className;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
