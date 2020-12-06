#pragma once

// Project includes
#include "Component.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Interface of ComponentFactory.
     */
    class IComponentFactory
    {
        public:
            virtual ~IComponentFactory() = default;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType