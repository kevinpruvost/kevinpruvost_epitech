/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#pragma once

#include "Destination.hpp"

namespace Federation
{
    class Ship;

namespace Starfleet
{
    class Captain;
    class Ship;

    class Ensign;
} // !Starfleet
} // !Federation

namespace Borg
{
    class Ship;
} // !Borg

namespace WarpSystem
{
    class QuantumReactor;
    class Core;
} // !WarpSystem

class ShipBase
{
public:
    ShipBase(short maxWarp, int torpedo = 0, int shield = 100);
    ~ShipBase();

public:
    bool move(int warp, Destination d);
    bool move(int warp);
    bool move(Destination d);
    bool move();

public:
    int getShield();
    void setShield(int shield);
    int getTorpedo();
    void setTorpedo(int torpedo);

protected:
    short       _maxWarp;

    WarpSystem::Core * _core = nullptr;
    Destination _location;
    Destination _home;

    int _shield;
    int _photonTorpedo;
};

class WarpSystem::QuantumReactor
{
public:
    QuantumReactor();
    ~QuantumReactor();

public:
    bool isStable();
    void setStability(bool stability);

private:
    bool _stability;
};

class WarpSystem::Core
{
public:
    Core(WarpSystem::QuantumReactor * coreReactor);
    ~Core();

public:
    WarpSystem::QuantumReactor * checkReactor();

private:
    WarpSystem::QuantumReactor * _coreReactor = nullptr;
};
