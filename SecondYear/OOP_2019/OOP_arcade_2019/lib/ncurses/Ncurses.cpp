/*
** EPITECH PROJECT, 2020
** Ncurses.cpp
** File description:
** ncurses class
*/

#include "Ncurses.hpp"

Ncurses::Ncurses(ArcadeContent & arcadeContent)
    : ADisplayModule(arcadeContent, "Ncurses")
{
    create_newwin(MAP_WIDTH/2, MAP_HEIGHT/2, 0, 0);
}

Ncurses::~Ncurses()
{
    endwin();
}

void Ncurses::create_newwin(int height, int width, int starty, int startx)
{
    newterm(NULL, stdin, stdin);
    curs_set(false);
    keypad(stdscr,TRUE);
    nodelay(stdscr, TRUE);
    noecho();

    start_color();

    if (has_colors() == FALSE) {
        endwin();
        throw EXCEPTION("Your terminal does not support color");
    }
}

int power(int a, int b)
{
    int res = a;
    for (int i = 1; i != b; ++i)
        res *= a;
    return res;
}

int octalToDecimal(int octal)
{
    int decimalNumber = 0, i = 0;

    while(octal != 0)
    {
        decimalNumber += (octal%10) * pow(8,i);
        ++i;
        octal/=10;
    }
    return decimalNumber;
}

void Ncurses::updateEvent()
{
	int ch = getch();
    refresh();

    if (ch == ERR)
        return;

    if (ch == KEY_LEFT || ch == 'q')
        setKey(ArcadeEvent::KeyValue::LEFT);
    else if (ch == (KEY_RIGHT) || ch == 'd')
        setKey(ArcadeEvent::KeyValue::RIGHT);
    else if (ch == KEY_UP || ch == 'z')
        setKey(ArcadeEvent::KeyValue::UP);
    else if (ch == KEY_DOWN || ch == 's')
        setKey(ArcadeEvent::KeyValue::DOWN);
    else if (ch == KEY_EXIT || ch == KEXIT)
        setKey(ArcadeEvent::KeyValue::ESCAPE);
    else if (ch == KEY_ENTER || ch == '\n')
        setKey(ArcadeEvent::KeyValue::ENTER);
    else if (ch == 'x')
        setKey(ArcadeEvent::KeyValue::EXIT);
    else if (ch == 'm')
        setKey(ArcadeEvent::KeyValue::MAINMENU);
    else if (ch == '&')
        changePrevGraphical();
    else if (ch == 169)                     //é
        changeNextGraphical();
    else if (ch == '"')
        changePrevGame();
    else if (ch == '\'')
        changeNextGame();
}

void Ncurses::setExtraTexture()
{

}

void Ncurses::display()
{
    int y = 0;
    clear();

    _colorMap.clear();
    short int colorPair = 0;
    for (const auto & spriteInfo : _spriteInfos)
    {
        init_pair(colorPair, spriteInfo.second.textColor,
                             spriteInfo.second.fondColor);
        _colorMap.insert(std::make_pair(spriteInfo.first, colorPair++));
    }

    for (int i = 0; i < MAP_WIDTH; ++i, y+=2) {
        for (int j = 0, x = 0; j < MAP_HEIGHT; ++j, x+=1) {
            std::string car;
            car += _spriteInfos[arcadeMap()[i][j]].replaceChar[0];
            car += _spriteInfos[arcadeMap()[i][j]].replaceChar[1];
            attron(COLOR_PAIR(_colorMap[arcadeMap()[i][j]]));
            mvprintw(x, y, car.c_str());
            attroff(COLOR_PAIR(_colorMap[arcadeMap()[i][j]]));
        }
    }
    refresh();
}