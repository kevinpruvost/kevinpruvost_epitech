/*
** EPITECH PROJECT, 2020
** ArcadeDLLoader.cpp
** File description:
** arrcade dl loader
*/

#include "ArcadeDLLoader.hpp"

template class ArcadeDLLoader<IDisplayModule>;
template class ArcadeDLLoader<IGameModule>;

template<class T>
ArcadeDLLoader<T>::ArcadeDLLoader(const std::string & libName)
    : DLLoader(libName)
{
}

template<class T>
ArcadeDLLoader<T>::~ArcadeDLLoader()
{
}

// getInstance -----------------------------------------------------------------

template IDisplayModule * ArcadeDLLoader<IDisplayModule>::getInstance(
    const std::string & funcName, ArcadeContent & arcadeContent) const;
template IGameModule * ArcadeDLLoader<IGameModule>::getInstance(
    const std::string & funcName, ArcadeContent & arcadeContent) const;

template<class T>
T * ArcadeDLLoader<T>::getInstance(const std::string & funcName, ArcadeContent & content) const
{
    T * (* baseCreator)(ArcadeContent & content) =
        reinterpret_cast<T *(*)(ArcadeContent &)>(dlsym(_lib, funcName.c_str()));

    if (baseCreator)
        return baseCreator(content);

    return nullptr;
}
