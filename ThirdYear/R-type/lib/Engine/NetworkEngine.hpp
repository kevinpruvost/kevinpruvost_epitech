#pragma once

//Project includes
#include "Components/AllComponents.hpp"
#include "Network/Rfc.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Serves as utilities for the network part.
     */
    class NetworkEngine
    {
        static Rfc::ComponentTypeId GetComponentTypeIdFromComponent(const std::weak_ptr<Component>& component);
        static Rfc::ComponentTypeId GetComponentTypeIdFromComponent(Component& component);
        
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
