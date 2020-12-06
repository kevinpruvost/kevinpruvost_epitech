
#include <iostream>
#include "Errors.hpp"
#include "WaterReclaimer.hpp"

WaterReclaimer::WaterReclaimer()
    : _water(0),
      _started(false)
{
}

void
WaterReclaimer::start()
{
    if (_water <= 0)
    {
        throw MissionCriticalError("Not enough water to achieve the mission.",
                               "WaterReclaimer");
    }
    else
    {
        if (_started)
        {
            _started = false;
            return;
        }
        _water -= 10;
        _started = true;
    }
}

void
WaterReclaimer::useWater(int water)
{
    if (!_started)
    {
        throw UserError("Cannot use water if the reclaimer hasn't started.",
                        "WaterReclaimer");
        return;
    }
    if (water < 0)
    {
        throw UserError("Water use should be positif.", "WaterReclaimer");
        return;
    }
    if (_water - water >= 0)
        _water -= water;
    else
    {
        throw LifeCriticalError("Cannot use water, not enough in the reclaimer.",
                                "WaterReclaimer");
    }
}

void
WaterReclaimer::generateWater()
{
    if (_started)
    {
        throw NasaError("Cannot generate water, reclaimer already full.",
                        "WaterReclaimer");
    }
    else
        _water += 10;
}
