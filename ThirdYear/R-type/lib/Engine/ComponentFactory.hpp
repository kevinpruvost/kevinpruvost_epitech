#pragma once

// Project includes
#include "IComponentFactory.hpp"
#include "ComponentArray.hpp"

#include "DebugController.hpp"

// C++ includes
#include <unordered_map>
#include <memory>
#include <list>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Creates components, registers them and assigns their signatures here.
     */
    class ComponentFactory : virtual public IComponentFactory
    {
    public:
        ComponentFactory();
        ~ComponentFactory();

        /**
         * @brief Registers a component of type T
         */
        template<typename T>
        void RegisterComponent()
        {
            std::string typeName = typeid(T).name();

            if (__componentSignaturesByNames.find(typeName) != __componentSignaturesByNames.end())
                throw CRITICAL_EXCEPTION("Component named (" + typeName + "), also registered was trying to be registered once more.");

            __componentSignaturesByNames.insert({ typeName, __movingSignature++ });
            __componentArraysByNames.insert({ typeName, std::make_shared<ComponentArray<T>>() });

            DEBUG_LOG("Component of type '" + std::string(typeName) + "' (id : " +  std::to_string(__movingSignature - 1) + ") registered !");
        }

        /**
         * @brief Gets Component signature of the component of type T.
         * \return 
         */
        template<typename T>
        ComponentSignature GetComponentSignature()
        {
            std::string typeName = typeid(T).name();

            if (__componentSignaturesByNames.find(typeName) == __componentSignaturesByNames.end())
                throw CRITICAL_EXCEPTION("Component '" + typeName + "' not registered.");
            return __componentSignaturesByNames[typeName];
        }

        /**
         * @brief Adds Component of type T to the entity of id 'id'.
         * 
         * \param id
         * \param component
         * \return index of the newly added component
         */
        template<typename T>
        size_t AddComponent(EntityId id, T component)
        {
            DEBUG_LOG("Adding Component " << typeid(T).name() << " to " << id);
            return GetComponentArray<T>()->InsertComponent(id, component);
        }

        /**
         * @brief Removes every components from entity of id 'id'.
         * 
         * \param id
         */
        template<typename T>
        void RemoveComponents(EntityId id)
        {
            GetComponentArray<T>()->RemoveComponents(id);
        }

        /**
         * @brief Removes the given component from the entity of id 'id'.
         * 
         * \param id
         * \param component
         */
        template<typename T>
        void RemoveComponent(EntityId id, const T& component)
        {
            GetComponentArray<T>()->RemoveComponent(id, component);
        }

        /**
         * @brief Removes a component of index 'index' in its assigned component array
         * from the entity of id 'id'.
         *
         * \param id
         * \param size
         */
        template<typename T>
        void RemoveComponent(EntityId id, const size_t index = 0)
        {
            GetComponentArray<T>()->RemoveComponent(id, index);
        }

        /**
         * @brief Gets the component of 'index' from the entity of id 'id'.
         * 
         * \param id
         * \param index
         * \return 
         */
        template<typename T>
        T& GetComponent(EntityId id, size_t index = 0)
        {
            return GetComponentArray<T>()->GetComponent(id, index);
        }

        Component & GetComponent(std::string className, EntityId id, size_t index = 0)
        {
            if (__componentArraysByNames.find(className) == __componentArraysByNames.end())
                throw CRITICAL_EXCEPTION("Component not registered.");

            auto compArray = __componentArraysByNames.at(className);
            auto convertedArray = std::static_pointer_cast<ComponentArray<Component>>(compArray);
            return convertedArray->GetComponent(id, index);
        }

        /**
         * @brief Gets the component ptr of 'index' from the entity of id 'id'.
         *
         * \param id
         * \param index
         * \return
         */
        template<typename T>
        std::weak_ptr<T> GetComponentPtr(EntityId id, size_t index = 0)
        {
            return GetComponentArray<T>()->GetComponentPtr(id, index);
        }

        /**
         * @brief Checks if the entity has a component of type T.
         *
         * \param id
         * \param index
         * \return
         */
        template<typename T>
        bool HasComponent(EntityId id)
        {
            return GetComponentArray<T>()->HasComponent(id);
        }

        /**
         * @brief Tells to the component arrays that the entity of id 'id' has been destroyed,
         * and so destroys every components it had.
         * 
         * \param id
         */
        void EntityDestroyed(EntityId id)
        {
            for (auto& componentArray : __componentArraysByNames)
                componentArray.second->EntityDestroyed(id);
        }

        /**
         * @brief Finds an entity based on one of its component.
         *
         * \param component
         * \return
         */
        template<typename T>
        EntityId FindParentEntity(const T& component)
        {
            return GetComponentArray<T>()->FindParentEntity(component);
        }

        /**
         * @brief Finds an entity based on one of its component.
         *
         * \param component
         * \return
         */
        template<typename T>
        EntityId FindParentEntity(const T & component, const std::string & className)
        {
            for (auto& pair : __componentArraysByNames)
            {
                DEBUG_LOG("Array :" << pair.first);
            }
            if (__componentArraysByNames.find(className) == __componentArraysByNames.end())
                throw CRITICAL_EXCEPTION("Couldn't find array of components '" + className + "'.");
            return __componentArraysByNames.at(className)->FindParentEntityWithComponent(component);
        }

        /**
         * @brief Used to get every components of a type T
         * \return
         */
        template<typename T>
        std::list<std::weak_ptr<T>> GetComponents()
        {
            std::string typeName = typeid(T).name();

            if (__componentArraysByNames.find(typeName) == __componentArraysByNames.end())
                throw MINOR_EXCEPTION("Component '" + typeName + "' not found.");

            return GetComponentArray<T>()->GetComponents();
        }

        std::list<std::weak_ptr<Component>> GetEveryComponents()
        {
            std::list<std::weak_ptr<Component>> components;
            for (auto& pair : __componentArraysByNames)
            {
                auto newList = pair.second->GetConvertedComponents();
                components.splice(components.end(), newList);
            }
            return components;
        }

    private:
        /**
         * @brief Gets the component array linked to T.
         * 
         * \return 
         */
        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray()
        {
            std::string typeName = typeid(T).name();

            if (__componentArraysByNames.find(typeName) == __componentArraysByNames.end())
                throw CRITICAL_EXCEPTION("Component '" + typeName + "' not registered.");
            return std::static_pointer_cast<ComponentArray<T>>(__componentArraysByNames.at(typeName));
        }

    private:
        std::unordered_map<std::string, ComponentSignature> __componentSignaturesByNames;
        std::unordered_map<std::string, std::shared_ptr<IComponentArray>> __componentArraysByNames;

        ComponentSignature __movingSignature = 0;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
