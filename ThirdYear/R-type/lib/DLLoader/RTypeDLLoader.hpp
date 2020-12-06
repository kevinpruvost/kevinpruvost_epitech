/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** IDllLoader
*/

#pragma once

#include "Entity.hpp"
#include "System.hpp"
#include "DLLoader.hpp"
#include "RSystem.hpp"
#include "REngine.hpp"

namespace RType
{
namespace Common
{
namespace DLLoader
{
/**
 * @brief Load a RType shared object
 * 
 */
template<class T>
class RTypeDLLoader : virtual public DLLoader {
    public:
        RTypeDLLoader(const std::string & name);
        ~RTypeDLLoader();

        T * getInstance(const std::string & name, RType::Common::Engine::REngine & engine);
        std::function<T * (RType::Common::Engine::REngine &)> getLoadedFunction(const std::string & name);

        //Overload Operator
        bool operator== (std::nullptr_t);
};
}; // !RType::Common::DLLoaderR
}; // !RType::Common
}; // !RType