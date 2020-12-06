/*
** EPITECH PROJECT, 2020
** ArcadeEvent.hpp
** File description:
** arcade event
*/

#pragma once

class ArcadeEvent
{
public:
    enum KeyValue
    {
        NO_KVALUE = -1,
        LEFT, RIGHT, UP, DOWN,
        ESCAPE, ENTER,
        EXIT, MAINMENU,
        CHANGE_GAME, CHANGE_GRAPH
    };

public:
    ArcadeEvent(bool pressed = false, bool released = false,
                KeyValue keyValue = KeyValue::NO_KVALUE,
                int gameId = NO_KVALUE,
                int displayId = NO_KVALUE);
    ~ArcadeEvent();

    bool & isPressed()                     { return _pressed;   }
    const bool isPressed() const           { return _pressed;   }
    bool & isReleased()                    { return _released;  }
    const bool isReleased() const          { return _released;  }
    int & getKeyValue()                    { return _keyValue;  }
    const int getKeyValue() const          { return _keyValue;  }
    int & getGameId()                      { return _gameId;    }
    const int getGameId() const            { return _gameId;    }
    int & getDisplayId()                   { return _displayId; }
    const int getDisplayId() const         { return _displayId; }

private:
    bool _pressed = false;
    bool _released = false;
    int _keyValue = NO_KVALUE;
    int _gameId = NO_KVALUE;
    int _displayId = NO_KVALUE;
};