#pragma once

// Project includes
#include "IComponentArray.hpp"
#include "Component.hpp"
#include "Exception.hpp"
#include "DebugController.hpp"

// C++ includes
#include <assert.h>
#include <unordered_map>
#include <memory>
#include <set>
#include <list>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains derived classes of Component.
     * Be aware, 'T' has to be a derived class of Component.
     * If this condition is not applied, a throw or an assert will be throwed.
     */ 
    template<typename T>
    class ComponentArray : public IComponentArray
    {
        public:
            ComponentArray()
            {
                static_assert(std::is_base_of<Component, T>() == true);
            }
            ~ComponentArray() = default;

            /**
             * @brief Inserts 'component' into entity of id 'id'.
             * 
             * \param id
             * \param component
             * \return 
             */
            size_t InsertComponent(const EntityId id, T component)
            {
                if (__componentsByEntityIds.find(id) != __componentsByEntityIds.end()
                 && __componentsByEntityIds[id].size() >= UINT16_MAX)
                    throw CRITICAL_EXCEPTION("Too much components");

                ((Component &)component).entityId = id;

                if (__componentsByEntityIds.find(id) != __componentsByEntityIds.end())
                    __componentsByEntityIds[id].push_back(std::shared_ptr<T>(new T(component)));
                else
                    __componentsByEntityIds[id] = std::vector<std::shared_ptr<T>>({ std::shared_ptr<T>(new T(component)) });

                return __componentsByEntityIds[id].size() - 1;
            }

            /**
             * @brief Removes 'component' of the entity of id 'id'.
             * 
             * \param id
             * \param component
             */
            void RemoveComponent(const EntityId id, const T & component)
            {
                // Checks if id has a component here.
                if (__componentsByEntityIds.find(id) == __componentsByEntityIds.end())
                    throw MINOR_EXCEPTION("Component not found for id : " + std::to_string(id));

                for (auto & ite = __componentsByEntityIds[id].begin(); ite != __componentsByEntityIds[id].end(); ++ite)
                {
                    if ((*ite).get() == component)
                    {
                        __componentsByEntityIds[id].erase(ite);
                        return;
                    }
                }
                throw MINOR_EXCEPTION("Component not found.");
            }

            /**
             * @brief Removes 'component' of the entity of id 'id'.
             *
             * \param id
             * \param component
             */
            void RemoveComponent(const EntityId id, const size_t index)
            {
                // Checks if id has a component here.
                if (__componentsByEntityIds.find(id) == __componentsByEntityIds.end() || index >= __componentsByEntityIds[id].size())
                    throw MINOR_EXCEPTION("Component not found for id : " + std::to_string(id));

                __componentsByEntityIds[id].erase(__componentsByEntityIds[id].begin() + index);
            }

            /**
             * @brief Remove every components from entity of id 'id'.
             * 
             * \param id
             */
            void RemoveComponents(const EntityId id)
            {
                EntityDestroyed(id);
            }

            /**
             * @brief Gets Component of type T from the entity of id 'id', if there's multiple components of the same type
             * in the entity, then 'index' can be speicified (its default value is 0).
             * 
             * \param id
             * \param index
             * \return 
             */
            T & GetComponent(const EntityId id, size_t index = 0)
            {
                if (__componentsByEntityIds.find(id) == __componentsByEntityIds.end())
                    throw MINOR_EXCEPTION("Component '" + typeid(T).name() + "' not found for id : " + std::to_string(id));

                return *__componentsByEntityIds[id][index];
            }

            /**
             * @brief Gets Component of type T from the entity of id 'id', if there's multiple components of the same type
             * in the entity, then 'index' can be speicified (its default value is 0).
             *
             * \param id
             * \param index
             * \return
             */
            std::weak_ptr<T> GetComponentPtr(const EntityId id, size_t index = 0)
            {
                if (__componentsByEntityIds.find(id) == __componentsByEntityIds.end())
                    throw MINOR_EXCEPTION("Component '" + typeid(T).name() + "' not found for id : " + std::to_string(id));

                return __componentsByEntityIds[id][index];
            }

            /**
             * @brief Gets Component of type T from the entity of id 'id', if there's multiple components of the same type
             * in the entity, then 'index' can be speicified (its default value is 0).
             *
             * \param id
             * \param index
             * \return
             */
            bool HasComponent(const EntityId id)
            {
                return __componentsByEntityIds.find(id) != __componentsByEntityIds.end();
            }

            /**
             * @brief Returns a list of components of type T.
             * 
             * \return 
             */
            std::list<std::weak_ptr<T>> GetComponents()
            {
                std::list<std::weak_ptr<T>> comps;
                for (auto& pair : __componentsByEntityIds)
                {
                    for (auto& comp : pair.second)
                    {
                        comps.push_back(std::weak_ptr<T>(comp));
                    }
                }
                return comps;
            }

            /**
             * @brief Finds an entity based on one of its component.
             * 
             * \param component
             * \return 
             */
            EntityId FindParentEntity(const T & component)
            {
                for (auto & entityPair : __componentsByEntityIds)
                {
                    for (auto& componentCmp : entityPair.second)
                    {
                        if (std::static_pointer_cast<Component>(componentCmp)->id == static_cast<const Component *>(&component)->id)
                        {
                            return entityPair.first;
                        }
                    }
                }
                throw MINOR_EXCEPTION("Didn't find parent entity.");
            }
            
            EntityId FindParentEntityWithComponent(const Component & component) override
            {
                DEBUG_LOG("Je suis adjzquidqjz");
                for (auto& entityPair : __componentsByEntityIds)
                {
                    for (auto& componentCmp : entityPair.second)
                    {
                        if (std::static_pointer_cast<Component>(componentCmp)->id == component.id)
                        {
                            return entityPair.first;
                        }
                        DEBUG_LOG("Je suis ooeuf");
                    }
                }
                throw MINOR_EXCEPTION("Didn't find parent entity.");
            }

            /**
             * @brief Notice the array that the entity does not exist anymore,
             * and so, destroys every components it had.
             * 
             * \param id
             */
            void EntityDestroyed(const EntityId id) override
            {
                // Checks if id has a component here.
                if (__componentsByEntityIds.find(id) == __componentsByEntityIds.end())
                    throw MINOR_EXCEPTION("Component not found for id : " + std::to_string(id));

                __componentsByEntityIds[id].clear();
                __componentsByEntityIds.erase(id);
            }

            std::list<std::weak_ptr<Component>> GetConvertedComponents() override
            {
                std::list<std::weak_ptr<Component>> components;
                for (auto& pair : __componentsByEntityIds)
                {
                    for (auto & component : pair.second)
                    {
                        components.push_back(std::weak_ptr<Component>(component));
                    }
                }
                return components;
            }

        private:
            std::unordered_map<EntityId, std::vector<std::shared_ptr<T>>> __componentsByEntityIds;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
