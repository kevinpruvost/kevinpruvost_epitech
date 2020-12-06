/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "WarpSystem.hpp"

// ShipBase --------------------------------------------------------------------

ShipBase::ShipBase(short maxWarp, int torpedo, int shield)
    : _maxWarp { maxWarp }
    , _core { nullptr }
    , _shield { shield }
    , _photonTorpedo { torpedo }
{
}

ShipBase::~ShipBase()
{
}

bool ShipBase::move()
{
    if (!_core || !_core->checkReactor())
        return false;
    if (_core->checkReactor()->isStable())
    {
        _location = _home;
        return true;
    }
    return false;
}

bool ShipBase::move(Destination d)
{
    if (!_core || !_core->checkReactor())
        return false;
    if (_core->checkReactor()->isStable() && d != _location)
    {
        _location = d;
        return true;
    }
    return false;
}

bool ShipBase::move(int warp)
{
    if (!_core || !_core->checkReactor())
        return false;
    if (_core->checkReactor()->isStable() && warp <= _maxWarp)
    {
        _location = _home;
        return true;
    }
    return false;
}

bool ShipBase::move(int warp, Destination d)
{
    if (!_core || !_core->checkReactor())
        return false;
    if (warp <= _maxWarp && d != _location && _core->checkReactor()->isStable())
    {
        _location = d;
        return true;
    }
    return false;
}

int ShipBase::getShield()
{
    return _shield;
}

int ShipBase::getTorpedo()
{
    return _photonTorpedo;
}

void ShipBase::setShield(int shield)
{
    _shield = shield;
}

void ShipBase::setTorpedo(int torpedo)
{
    _photonTorpedo = torpedo;
}

// QuantumReactor --------------------------------------------------------------

WarpSystem::QuantumReactor::QuantumReactor()
    : _stability { true }
{
}

WarpSystem::QuantumReactor::~QuantumReactor()
{
}

bool WarpSystem::QuantumReactor::isStable()
{
    return _stability;
}

void WarpSystem::QuantumReactor::setStability(bool stability)
{
    _stability = stability;
}

// Core ------------------------------------------------------------------------

WarpSystem::Core::Core(QuantumReactor * coreReactor)
    : _coreReactor { coreReactor }
{
}

WarpSystem::Core::~Core()
{
}

WarpSystem::QuantumReactor * WarpSystem::Core::checkReactor()
{
    return _coreReactor;
}
