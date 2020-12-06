/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** RtypeDllLoader
*/

#include "RTypeDLLoader.hpp"

using namespace RType::Common::DLLoader;

template class RTypeDLLoader<RType::Common::Engine::Entity>;
//template class RTypeDLLoader<RType::Common::Engine::Component>;
//template class RTypeDLLoader<RType::Common::Engine::RSystem>;

/**
 * @brief Construct a new RTypeDLLoader<T>::RTypeDLLoader object
 * 
 * @param name Absolute path of the shared object
 */
template<class T>
RTypeDLLoader<T>::RTypeDLLoader(const std::string & name)
    : DLLoader (name)
{
}

/**
 * @brief Destroy the RTypeDLLoader<T>::RTypeDLLoader object
 * 
 */
template<class T>
RTypeDLLoader<T>::~RTypeDLLoader()
{
}


template std::function<RType::Common::Engine::Entity * (RType::Common::Engine::REngine &)> RTypeDLLoader<RType::Common::Engine::Entity>::getLoadedFunction(const std::string & name);
//template std::function<RType::Common::Engine::Component * (RType::Common::Engine::REngine &)> RTypeDLLoader<RType::Common::Engine::Component>::getLoadedFunction(const std::string & name);
//template std::function<RType::Common::Engine::RSystem * (RType::Common::Engine::REngine &)> RTypeDLLoader<RType::Common::Engine::RSystem>::getLoadedFunction(const std::string & name);

/**
 * @brief Get the previously name function
 * 
 * @param name the function's name
 * @return T pointer to the requested function
 */
template<class T>
std::function<T * (RType::Common::Engine::REngine &)> RTypeDLLoader<T>::getLoadedFunction(const std::string & name)
{
    if (getLib() == nullptr)
        return nullptr;

    T * (* function)(RType::Common::Engine::REngine &) = nullptr;
    
    #ifdef __unix__
        function = reinterpret_cast<T * (*)(RType::Common::Engine::REngine &)>(linux_dll_sym(getLib(), name.c_str()));
    #elif _WIN32
        function = reinterpret_cast<T * (*)(RType::Common::Engine::REngine &)>(windows_dll_sym((HINSTANCE)getLib(), name.c_str()));
    #endif
    return function;
}

template RType::Common::Engine::Entity * RTypeDLLoader<RType::Common::Engine::Entity>::getInstance(const std::string & name, RType::Common::Engine::REngine & engine);
//template RType::Common::Engine::Component * RTypeDLLoader<RType::Common::Engine::Component>::getInstance(const std::string & name, RType::Common::Engine::REngine & engine);
//template RType::Common::Engine::RSystem * RTypeDLLoader<RType::Common::Engine::RSystem>::getInstance(const std::string & name, RType::Common::Engine::REngine & engine);

/**
 * @brief 
 * 
 * @param name Name of the function to retrieve
 * @return T* Can be either nullptr or a pointer to the address symbol
 */
template<class T>
T * RTypeDLLoader<T>::getInstance(const std::string & name, RType::Common::Engine::REngine & engine)
{
    if (getLib() == nullptr)
        return nullptr;

    T * symResult = nullptr;

    T * (* function)(RType::Common::Engine::REngine &) = nullptr;
    
    #ifdef __unix__
        function = reinterpret_cast<T * (*)(RType::Common::Engine::REngine &)>(linux_dll_sym(getLib(), name.c_str()));
    #elif _WIN32
        function = reinterpret_cast<T * (*)(RType::Common::Engine::REngine &)>(windows_dll_sym((HINSTANCE)getLib(), name.c_str()));
    #endif

    if (!function)
        return nullptr;
    symResult = function(engine);
    if (!symResult)
        return nullptr;
    return symResult;
}

/**
 * @brief Overload operator "=="
 * 
 * @param null nullptr
 * @return true The current library is null
 * @return false The current library is not null
 */
template <class T>
bool RTypeDLLoader<T>::operator== (std::nullptr_t null)
{
    return (getLib() == null);
}
