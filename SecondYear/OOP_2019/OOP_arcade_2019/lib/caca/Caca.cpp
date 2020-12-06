/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Caca
*/

#include "Caca.hpp"

ArcadeCaca::ArcadeCaca(ArcadeContent & arcadeContent)
    : ADisplayModule(arcadeContent, "Caca")
{
    _dp = caca_create_display(NULL);
    _cv = caca_get_canvas(_dp);
    caca_set_display_title(_dp, "Arcade Machine - Caca Display Mode");
    caca_set_color_ansi(_cv, CACA_WHITE, CACA_BLACK);
    caca_refresh_display(_dp);
}

int traduct(int color)
{
    switch (color) {
        case 0:
            return CACA_BLACK;
        case 1:
            return CACA_RED;
        case 2:
            return CACA_GREEN;
        case 3:
            return CACA_YELLOW;
        case 4:
            return CACA_BLUE;
        case 5:
            return CACA_MAGENTA;
        case 6:
            return CACA_CYAN;
        case 7:
            return CACA_WHITE;
        default:
            return CACA_BLACK;
    }
}

void ArcadeCaca::display()
{
    int y = 0;
    caca_clear_canvas(_cv);

    for (int i = 0; i < MAP_WIDTH; ++i, y+=2) {
        for (int j = 0, x = 0; j < MAP_HEIGHT; ++j, x+=1) {
            std::string car;
            caca_set_color_ansi(_cv, traduct(_spriteInfos[arcadeMap()[i][j]].textColor), traduct( _spriteInfos[arcadeMap()[i][j]].fondColor));
            car +=  _spriteInfos[arcadeMap()[i][j]].replaceChar[0];
            car +=  _spriteInfos[arcadeMap()[i][j]].replaceChar[1];
            caca_put_str(_cv, y, x, car.c_str());
        }
    }
    caca_set_color_ansi(_cv, CACA_BLACK, CACA_BLACK);
    caca_refresh_display(_dp);
}

void ArcadeCaca::setExtraTexture()
{
}

void ArcadeCaca::updateEvent()
{
    int ch = 0;

    if (caca_get_event(_dp, CACA_EVENT_ANY, &_ev, 0)) {
        if(!(caca_get_event_type(&_ev) & CACA_EVENT_KEY_PRESS))
            return;
    ch = caca_get_event_key_ch(&_ev);
    if (ch == 'q' || ch == 275)
        setKey(ArcadeEvent::KeyValue::LEFT);
    else if (ch == 'd' || ch == 276)
        setKey(ArcadeEvent::KeyValue::RIGHT);
    else if (ch == 'z' || ch == 273)
        setKey(ArcadeEvent::KeyValue::UP);
    else if (ch == 's' || ch == 274)
        setKey(ArcadeEvent::KeyValue::DOWN);
    else if (ch == 'x')
        setKey(ArcadeEvent::KeyValue::EXIT);
    else if (ch == 27)
        setKey(ArcadeEvent::KeyValue::ESCAPE);
    else if (ch == 13 || ch == ' ')
        setKey(ArcadeEvent::KeyValue::ENTER);
    else if (ch == 'm')
        setKey(ArcadeEvent::KeyValue::MAINMENU);
    else if (ch == 38)
        changePrevGraphical();
    else if (ch == 233)
        changeNextGraphical();
    else if (ch == 34)
        changePrevGame();
    else if (ch == 39)
        changeNextGame();
    }
}

ArcadeCaca::~ArcadeCaca()
{
    caca_free_canvas(_cv);
    caca_free_display(_dp);
}