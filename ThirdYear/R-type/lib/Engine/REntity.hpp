#pragma once

// Project includes
#include "RAccess.hpp"
#include "RComponent.hpp"
#include "Entity.hpp"

// C++ includes
#include <functional>

#define RENTITY_MANDATORIES(className) public : \
    std::string ClassName() override { _className = typeid(className).name(); return _className; } \
    Entity * ProperCopy() const override { DEBUG_LOG("Copying " << typeid(className).name()); return new className(_engine); }

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Entity derivation that aims to be a simplified version of Entity
     * to handle, it has more practical methods to use.
     */
    class REntity : public Entity, public RAccess
    {
    public:
        REntity(REngine & engine);
        REntity(REngine& engine, EntityId id);
        REntity(const REntity & entity);
        ~REntity();

        virtual void Start() override;
        virtual void Tick() override;
        virtual void Update() override;
        virtual void UpdateEngine() final override;

        template<typename T>
        T& GetComponent(size_t index = 0) const { return _engine.get().GetComponent<T>(getId(), index); }

        template<typename T>
        std::weak_ptr<T> GetComponentPtr(size_t index = 0) const { return _engine.get().GetComponentPtr<T>(getId(), index); }

        template<typename T>
        size_t AddComponent() const
        {
            if (std::is_base_of<Component, T>())
                return _engine.get().AddComponent(getId(), T(_engine));
            return 0;
        }

        template<typename T>
        void RemoveComponent(size_t index = 0)
        {
            if (std::is_base_of<Component, T>())
                _engine.get().RemoveComponent<T>(index);
        }

        template<typename T>
        bool HasComponent()
        {
            return _engine.get().HasComponent<T>(getId());
        }

        void Destroy(EntityId id = Entity::EntityIdNull)
        {
            _engine.get().DestroyEntityId((id == Entity::EntityIdNull) ? getId() : id);
        }

    private:
        bool __idGiven = false;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
