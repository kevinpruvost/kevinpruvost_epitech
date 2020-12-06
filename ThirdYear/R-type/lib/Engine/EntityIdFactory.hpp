#pragma once

// Project includes
#include "IEntityIdFactory.hpp"
#include "Entity.hpp"

#include "DebugController.hpp"
#include "Exception.hpp"

// C++ includes
#pragma once

// C++ includes
#include <memory>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <list>

namespace RType
{
namespace Common
{
namespace Engine
{
    class EntityIdFactory;

    /**
     * @brief This is where the entities are stored, identified and where the ids are allocated.
     */
    class EntityIdFactory : virtual public IEntityIdFactory
    {
    public:
        EntityIdFactory();
        ~EntityIdFactory();

        /**
         * @brief Allocates an entity id.
         * 
         * \return 
         */
        EntityId ReserveEntityId() override;

        /**
         * @brief Reserves specific entity id.
         * 
         * \param id
         * \return 
         */
        EntityId ReserveEntityId(EntityId id);

        /**
         * @brief Frees an entity id.
         * 
         * \param id
         */
        void FreeEntityId(const EntityId id) override;

        /**
         * @brief Adds a component signature in an entity of id 'id'.
         * 
         * \param id
         * \param compSign
         */
        void AddComponentSignature(const EntityId id, const ComponentSignature compSign) override;

        /**
         * @brief Removes a component signature from an entity of id 'id'.
         * 
         * \param id
         * \param compSign
         */
        void RemoveComponentSignature(const EntityId id, const ComponentSignature compSign) override;

        /**
         * @brief Sets a signature to an entity of id 'id'.
         * 
         * \param id
         * \param signature
         */
        void SetSignature(const EntityId id, const EntitySignature & signature) override;

        /**
         * @brief Gets a signature from an entity of id 'id'.
         * 
         * \param id
         * \return 
         */
        EntitySignature GetSignature(const EntityId id) override;

        /**
         * @brief Registers an entity of type T.
         * 
         * \param entity
         */
        template<typename T>
        void RegisterEntity(const T& entity, const std::string & name)
        {
            if (!std::is_base_of<Entity, T>().value)
                throw CRITICAL_EXCEPTION("Trying to register non-entity type in EntityIdFactory." + typeid(T).name());

            if (__entityCopiesByClassName.find(name) != __entityCopiesByClassName.end())
                throw MINOR_EXCEPTION("Trying to register already registered class : " + typeid(T).name());

            __entityCopiesByClassName.insert({ name, std::shared_ptr<Entity>(entity.ProperCopy()) });
            FreeEntityId(__entityCopiesByClassName[name]->getId());
            DEBUG_LOG("Registered entity : " << name);

        }

        /**
         * @brief Registers an entity of type T.
         *
         * \param entity
         */
        template<typename T>
        void RegisterEntity()
        {
            if (!std::is_base_of<Entity, T>().value)
                throw CRITICAL_EXCEPTION("Trying to register non-entity type in EntityIdFactory." + typeid(T).name());

            std::string name = typeid(T).name();

            if (__entityCopiesByClassName.find(name) != __entityCopiesByClassName.end())
                throw MINOR_EXCEPTION("Trying to register already registered class : " + typeid(T).name());

            T entity;
            __entityCopiesByClassName.insert({ name, std::shared_ptr<Entity>(((Entity &)entity).ProperCopy()) });
            DEBUG_LOG("Registered entity : " << name);
        }

        /**
         * @brief Gets an array of the entity type names registered.
         * 
         * \return 
         */
        std::vector<std::string> GetEntityTypesNames();

        /**
         * @brief Creates an entity from a class name.
         * 
         * \param name
         * \return 
         */
        Entity & CreateEntityFromClassName(const std::string& name);

        /**
         * @brief Creates an entity from a class name.
         *
         * \param name
         * \return
         */
        Entity & Instantiate(const std::string& name);

        /**
         * @brief Creates an entity from a class name.
         *
         * \param name
         * \return
         */
        template<typename T>
        Entity & Instantiate()
        {
            return Instantiate(typeid(T).name());
        }

        /**
         * @brief Gets every entities of the factory.
         * 
         * \return 
         */
        std::list<std::weak_ptr<Entity>> GetEveryEntities();

        /**
         * @brief Stocks an entity in the map.
         * 
         * \param entity
         */
        std::weak_ptr<Entity> StockEntity(Entity& entity);

        bool HasEntityInStock(EntityId id);

        /**
         * @brief Creates an entity, give the constructor's needed parameters to construct the entity.
         * 
         * \param ...args
         * \return std::shared_ptr<T>
         */
        template<typename T, class ... Args>
        std::shared_ptr<T> CreateEntity(Args && ... args)
        {
            if (!std::is_base_of<Entity, T>::value)
                throw CRITICAL_EXCEPTION("Trying to create non-entity... entity ?");

            std::shared_ptr<T> ptr = std::shared_ptr<T>(new T(std::forward<Args>(args)...));
            std::shared_ptr<Entity> ptrToStock = std::static_pointer_cast<Entity>(ptr);
            EntityId newId = ptr->getId();
            __entities.insert({newId, ptrToStock});
            return ptr;
        }

        std::shared_ptr<Entity> GetEntityPtr(const EntityId id)
        {
            if (__entities.find(id) == __entities.end())
                throw MINOR_EXCEPTION("Can't find entity.");

            return __entities[id];
        }

        Entity & GetEntity(const EntityId id)
        {
            if (__entities.find(id) == __entities.end())
            {
                for (auto& entity : __entities)
                {
                    LOG_INFO("Entity " << entity.first << " of id " << entity.second->getId());
                }
                throw MINOR_EXCEPTION("Can't find entity.");
            }

            return *__entities[id];
        }

        void DestroyAll();

    private:
        std::unordered_map<EntityId, std::shared_ptr<Entity>> __entities;
        std::unordered_map<std::string, std::shared_ptr<Entity>> __entityCopiesByClassName;

        EntityId __movingId;
        std::set<EntityId> __freeIds;

        std::unordered_map<EntityId, EntitySignature> __componentSignaturesByIds;

        bool __destroying = false;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
