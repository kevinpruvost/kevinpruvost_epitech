#pragma once

// Project includes
#include "IREngine.hpp"
#include "Network/Rfc.hpp"
#include "Network/BinaryStructure.hpp"

#include "SystemFactory.hpp"
#include "EntityIdFactory.hpp"
#include "ComponentFactory.hpp"

// C++ includes
#include <memory>
#include <chrono>
#include <thread>
#include <cstring>
#include <functional>

#include <thread>
#include <mutex>
#include <condition_variable>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains every factories.
     * Constructs and contains every entities, components and systems.
     */
    class REngine : virtual public IREngine
    {
    public:
        REngine();
        ~REngine();

        /**
         * @brief Allocates an entity id.
         * 
         * \return 
         */
        EntityId CreateEntityId();

        /**
         * @brief Frees an entity id.
         * 
         * \param id
         */
        void DestroyEntityId(EntityId id);

        /**
         * @brief Registers an entity type.
         * 
         * \param entity
         */
        template<typename T>
        void RegisterEntity(const T & entity, const std::string & name = typeid(T).name())
        {
            __entityIdFactory->RegisterEntity<T>(entity, name);
            LOG_INFO("'" << name << "' registered.");
        }

        /**
         * @brief Gets an array of the entity type names.
         * 
         * \return 
         */
        std::vector<std::string> GetEntityTypesNames()
        {
            return __entityIdFactory->GetEntityTypesNames();
        }

        /**
         * @brief Creates an entity previously registered with the given name.
         * 
         * \param name
         * \return 
         */
        Entity CreateEntityFromClassName(const std::string& name)
        {
            auto entity = __entityIdFactory->CreateEntityFromClassName(name);
            auto signature = __entityIdFactory->GetSignature(entity.getId());
            __systemFactory->EntitySignatureChanged(entity.getId(), signature);
            __createdEntities.push_back(entity.getId());
            return entity;
        }

        /**
         * @brief Creates an entity with given id.
         * 
         * \param id
         * \return 
         */
        EntityId CreateEntityWithId(EntityId id);

        /**
         * @brief Registers a component.
         */
        template<typename T>
        void RegisterComponent(Rfc::ComponentTypeId typeId)
        {
            __componentFactory->RegisterComponent<T>();
            __componentNameByTypeId.insert({ typeId, typeid(T).name() });
            __componentTypeIdByName.insert({ typeid(T).name(), typeId });
            __componentSizeByName.insert({ typeid(T).name(), sizeof(T) });
            LOG_INFO("Component size : " << sizeof(T));
        }

        template<typename T>
        Rfc::ComponentTypeId GetComponentTypeId()
        {
            if (__componentTypeIdByName.find(typeid(T).name()) == __componentTypeIdByName.end())
                throw MINOR_EXCEPTION("Type id does not exist.");
            return __componentTypeIdByName[typeid(T).name()];
        }

        size_t GetComponentSize(Component & component)
        {
            if (__componentSizeByName.find(component.ClassName()) == __componentSizeByName.end())
                throw MINOR_EXCEPTION("Component size not stored.");
            return __componentSizeByName[component.ClassName()];
        }

        void UpdateComponent(EntityId entityId, Rfc::ComponentTypeId typeId, RType::Common::Udp::Entities::UpdateRequest updateRequest)
        {
            auto & compToUpdate = GetComponent(__componentNameByTypeId[typeId], entityId);
            compToUpdate.UpdateComponent(updateRequest);
        }

        /**
         * @brief Adds a component T to the entity of id 'id'.
         * 
         * \param id
         * \param component
         * \return index of the new component
         */
        template<typename T>
        size_t AddComponent(EntityId id, T component)
        {
            size_t index = __componentFactory->AddComponent<T>(id, component);

            auto signature = __entityIdFactory->GetSignature(id);
            signature.AddComponentSignature(__componentFactory->GetComponentSignature<T>());
            __entityIdFactory->SetSignature(id, signature);

            __systemFactory->EntitySignatureChanged(id, signature);
            __createdComponents.push_back(GetComponentPtr<T>(id));
            return index;
        }

        /**
         * Removes a component T from the entity of id 'id'.
         * 
         * \param id
         */
        template<typename T>
        void RemoveComponent(EntityId id, size_t index = 0)
        {
            __componentFactory->RemoveComponent<T>(id, index);

            auto signature = __entityIdFactory->GetSignature(id);
            signature.erase(__componentFactory->GetComponentSignature<T>());
            __entityIdFactory->SetSignature(id, signature);

            __systemFactory->EntitySignatureChanged(id, signature);
        }

        /**
         * Removes every components of type T from entity of id 'id'.
         *
         * \param id
         */
        template<typename T>
        void RemoveComponents(EntityId id)
        {
            __componentFactory->RemoveComponents<T>(id);

            auto signature = __entityIdFactory->GetSignature(id);
            signature.erase(__componentFactory->GetComponentSignature<T>());
            __entityIdFactory->SetSignature(id, signature);

            __systemFactory->EntitySignatureChanged(id, signature);
        }

        /**
         * @brief Gets component of type T at index 'index'.
         * 
         * \param id
         * \param index
         * \return 
         */
        template<typename T>
        T& GetComponent(EntityId id, size_t index = 0)
        {
            return __componentFactory->GetComponent<T>(id, index);
        }

        Component & GetComponent(std::string className, EntityId id, size_t index = 0)
        {
            return __componentFactory->GetComponent(className, id, index);
        }

        /**
         * @brief Gets component of type T at index 'index'.
         *
         * \param id
         * \param index
         * \return
         */
        template<typename T>
        std::weak_ptr<T> GetComponentPtr(EntityId id, size_t index = 0)
        {
            return __componentFactory->GetComponentPtr<T>(id, index);
        }

        /**
         * @brief Gets component of type T at index 'index'.
         *
         * \param id
         * \param index
         * \return
         */
        template<typename T>
        bool HasComponent(EntityId id)
        {
            return __componentFactory->HasComponent<T>(id);
        }

        /**
         * @brief Used to get every components of a type T
         * \return 
         */
        template<typename T>
        std::list<std::weak_ptr<T>> FindComponents()
        {
            return __componentFactory->GetComponents<T>();
        }
        
        /**
         * @brief Finds the entity id of the parent of the given 'component'.
         * 
         * \param component
         * \return 
         */
        template<typename T>
        EntityId FindParentEntity(const T& component)
        {
            return __componentFactory->FindParentEntity(component);
        }

        /**
         * @brief Finds the entity id of the parent of the given 'component'.
         *
         * \param component
         * \return
         */
        template<typename T>
        EntityId FindParentEntity(const T& component, const std::string & className)
        {
            return __componentFactory->FindParentEntity(component, className);
        }

        /**
         * @brief Gets the component signature of the component of type T.
         * 
         * \return 
         */
        template<typename T>
        ComponentSignature GetComponentSignature()
        {
            return __componentFactory->GetComponentSignature<T>();
        }

        /**
         * @brief Registers a system of type T and forwards 'args' to construct
         * the system in the system factory.
         * 
         * \param ...args
         * \return 
         */
        template<typename T, class ... Args>
        std::shared_ptr<T> RegisterSystem(Args && ... args)
        {
            return __systemFactory->RegisterSystem<T>(std::forward<Args>(args)...);
        }

        /**
         * @brief Sets the system signature.
         * 
         * \param signature
         */
        template<typename T>
        void SetSystemSignature(const EntitySignature & signature)
        {
            __systemFactory->SetSignature<T>(signature);
        }

        /**
         * @brief Adds a component signature to the system.
         *
         * \param systemName
         * \param signature
         */
        void AddComponentSignatureToSystem(const std::string & systemName, ComponentSignature signature)
        {
            __systemFactory->AddComponentSignature(systemName, signature);
        }

        /**
         * @brief Creates an entity from a class name.
         *
         * \param name
         * \return
         */
        Entity & Instantiate(const std::string& name)
        {
            return __entityIdFactory->Instantiate(name);
        }

        /**
         * @brief Creates an entity from a class name.
         *
         * \param name
         * \return
         */
        template<typename T>
        Entity & Instantiate()
        {
            return __entityIdFactory->Instantiate<T>();
        }

        std::weak_ptr<Entity> StockEntity(Entity & entity)
        {
            DEBUG_LOG("Stocking : " << entity.ClassName());
            return __entityIdFactory->StockEntity(entity);
        }

        /**
         * @brief Checks if an entity exists.
         *
         * \param Entity entity
         * \return
         */
        bool EntityExists(const Entity & entity)
        {
            return __entityIdFactory->HasEntityInStock(entity.getId());
        }

        /**
         * @brief Checks if an entity exists.
         *
         * \param EntityId id
         * \return
         */
        bool EntityExists(const EntityId id)
        {
            return __entityIdFactory->HasEntityInStock(id);
        }

        Entity& GetEntity(const EntityId id)
        {
            return __entityIdFactory->GetEntity(id);
        }

        std::shared_ptr<Entity> GetEntityPtr(const EntityId id)
        {
            return __entityIdFactory->GetEntityPtr(id);
        }

        /**
         * @brief Creates an entity, give the constructor's needed parameters to construct the entity.
         * 
         * \param ...args
         * \return std::shared_ptr<T>
         */
        template<typename T, class ... Args>
        std::shared_ptr<T> CreateEntity(Args && ... args)
        {
            return __entityIdFactory->CreateEntity<T>(std::forward<Args>(args)...);
        }

        float ComputeDeltaTime();

        bool Loop();

        void Clear();

        void Stop(bool callback);

        bool isStopped()
        {
            return __stop;
        }

        void LoopOnThread();

        std::list<std::weak_ptr<Entity>> GetAllEntities()
        {
            return __entityIdFactory->GetEveryEntities();
        }

        std::list<std::weak_ptr<Component>> GetAllComponents()
        {
            return __componentFactory->GetEveryComponents();
        }

        bool shouldTick();

        std::vector<std::weak_ptr<Component>> GetCreatedComponents();

        std::vector<EntityId> GetCreatedEntities()
        {
            auto createdEntities = __createdEntities;
            __createdEntities.clear();
            return createdEntities;
        }

        std::vector<EntityId> GetDestroyedEntityIds()
        {
            auto destroyedIds = __destructedEntities;
            __destructedEntities.clear();
            return destroyedIds;
        }

        void Pause(bool set);

        void WaitForPause();

    public:
        float deltaTime;
        std::thread::id mainThreadId = std::this_thread::get_id();
        float tickTime;
        int tickRate = 32;
        std::function<void()> callbackOnStop;

    private:
        std::shared_ptr<SystemFactory>    __systemFactory;
        std::shared_ptr<ComponentFactory> __componentFactory;
        std::shared_ptr<EntityIdFactory>  __entityIdFactory;

        std::chrono::steady_clock::time_point __startTime = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point __endTime;

        bool __stop = false;
        bool __lastLoopDone = false;

        bool __firstLoop = true;

        std::thread * __lauchingThread = nullptr;

        std::unordered_map<std::string, Rfc::ComponentTypeId> __componentTypeIdByName;
        std::unordered_map<Rfc::ComponentTypeId, std::string> __componentNameByTypeId;
        std::unordered_map<std::string, size_t> __componentSizeByName;

        std::vector<EntityId> __createdEntities;
        std::vector<std::weak_ptr<Component>> __createdComponents;
        std::vector<EntityId> __destructedEntities;

        std::mutex __mutex;
        std::condition_variable __cPause;
        bool __paused = false;
        bool __waiting = false;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
