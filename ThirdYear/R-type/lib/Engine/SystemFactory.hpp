#pragma once

// Project includes
#include "System.hpp"
#include "EntitySignature.hpp"

#include "Exception.hpp"
#include "DebugController.hpp"

// C++ includes
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <list>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains every systems and their signature.
     */
    class SystemFactory
    {
    public:
        SystemFactory();
        ~SystemFactory();

        /**
         * @brief Registers a system and accepts its construction arguments.
         * 
         * \param ...args
         * \return 
         */
        template<typename T, class ... Args>
        std::shared_ptr<T> RegisterSystem(Args && ... args)
        {
            const char* typeName = typeid(T).name();

            if (__systemsByNames.find(typeName) != __systemsByNames.end())
                throw MINOR_EXCEPTION("Trying to register already registered system.");

            auto system = std::make_shared<T>(std::forward<Args>(args)...);
            system->systemName = typeName;
            __systemsByNames.insert({ typeName, system });

            DEBUG_LOG("System '" + std::string(typeName) + "' registered !");

            return system;
        }

        /**
         * @brief Adds a component signature to the entity signature stored for the T system.
         * 
         * \param signature
         */
        void AddComponentSignature(const std::string & systemName, ComponentSignature signature)
        {
            const char* typeName = systemName.c_str();

            if (__systemsByNames.find(typeName) == __systemsByNames.end())
                throw CRITICAL_EXCEPTION("Trying to add signature to not registered system : " + typeName);

            __signaturesBySystemNames[typeName].insert(signature);
        }

        /**
         * @brief Sets a signature for the T system.
         * 
         * \param signature
         */
        template<typename T>
        void SetSignature(const EntitySignature & signature)
        {
            const char* typeName = typeid(T).name();

            if (__systemsByNames.find(typeName) == __systemsByNames.end())
                throw CRITICAL_EXCEPTION("Trying to set signature to not registered system.");

            __signaturesBySystemNames[typeName] = signature;
        }

        /**
         * @brief Informs the system factory that the entity of id 'id' has been destroyed.
         * 
         * \param id
         */
        void EntityDestroyed(EntityId id);

        /**
         * @brief Informs the system factory that the entity signature of the entity of id 'id' has been changed.
         *
         * \param id
         * \param signature
         */
        void EntitySignatureChanged(EntityId id, const EntitySignature & signature);

        /**
         * @brief Gets every systems in the factory.
         * 
         * \return 
         */
        std::list<std::weak_ptr<System>> GetEverySystems();

    private:
        std::unordered_map<std::string, EntitySignature> __signaturesBySystemNames;
        std::unordered_map<std::string, std::shared_ptr<System>> __systemsByNames;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType