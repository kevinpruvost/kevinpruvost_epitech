#pragma once

// Project includes
#include "IComponent.hpp"

// C++ includes
#include <set>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     *  @brief Derived from std::set<ComponentSignature>, serves as a signature for components.
     *  Its main purpose is to let the engine environement know how to copy the entity more easily.
     */
    class EntitySignature : public std::set<ComponentSignature>
    {
    public:
        using std::set<ComponentSignature>::set;
        EntitySignature();
        ~EntitySignature();

        void AddComponentSignature(ComponentSignature id);
        void RemoveComponentSignature(ComponentSignature id);
        void SetSignature(EntitySignature & signature);
        bool operator&(const EntitySignature & signature) const;
        bool operator|(const EntitySignature & signature) const;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
