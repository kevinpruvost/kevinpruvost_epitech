/*
** EPITECH PROJECT, 2020
** NamePanel.cpp
** File description:
** name
*/

#include "PacMan.hpp"

void PacMan::interactionsNamePanel()
{
    static const std::vector<std::vector<std::string>> buttons =
    {
        {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m"},
        {"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"},
        {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},
        {"save", "delete"}
    };

    if (KEY_VALUE == ArcadeEvent::KeyValue::UP)
    {
        --_cursor.first;
        if (_cursor.first < 0)
            _cursor.first = buttons.size() - 1;
        if (_cursor.second >= (int)buttons[_cursor.first].size())
            _cursor.second = buttons[_cursor.first].size() - 1;
    }
    else if (KEY_VALUE == ArcadeEvent::KeyValue::DOWN)
    {
        ++_cursor.first;
        if (_cursor.first >= (int)buttons.size())
            _cursor.first = 0;
        if (_cursor.second >= (int)buttons[_cursor.first].size())
            _cursor.second = buttons[_cursor.first].size() - 1;
    }
    else if (KEY_VALUE == ArcadeEvent::KeyValue::LEFT)
    {
        --_cursor.second;
        if (_cursor.second < 0)
            _cursor.second = buttons[_cursor.first].size() - 1;
    }
    else if (KEY_VALUE == ArcadeEvent::KeyValue::RIGHT)
    {
        ++_cursor.second;
        if (_cursor.second >= (int)buttons[_cursor.first].size())
            _cursor.second = 0;
    }
    else if (KEY_VALUE == ArcadeEvent::KeyValue::ENTER)
    {
        if (_cursor.first != (int)buttons.size() - 1)
        {
            if (_playerName.size() < 7)
                _playerName += buttons[_cursor.first][_cursor.second];
        }
        else
        {
            if (buttons[_cursor.first][_cursor.second] == "save")
                changePage(PacMan::PageId::INGAME);
            else if (buttons[_cursor.first][_cursor.second] == "delete")
                _playerName.clear();
        }
    }
    _namePanelCursorString = buttons[_cursor.first][_cursor.second];
}

void PacMan::drawNamePanel()
{
    static const std::vector<std::pair<std::string, std::pair<int, int>>> alphabetMap =
    {
        {"a", {CENTER_X - 12, CENTER_Y - 2}},
        {"b", {CENTER_X - 10, CENTER_Y - 2}},
        {"c", {CENTER_X - 8,  CENTER_Y - 2}},
        {"d", {CENTER_X - 6,  CENTER_Y - 2}},
        {"e", {CENTER_X - 4,  CENTER_Y - 2}},
        {"f", {CENTER_X - 2,  CENTER_Y - 2}},
        {"g", {CENTER_X,      CENTER_Y - 2}},
        {"h", {CENTER_X + 2,  CENTER_Y - 2}},
        {"i", {CENTER_X + 4,  CENTER_Y - 2}},
        {"j", {CENTER_X + 6,  CENTER_Y - 2}},
        {"k", {CENTER_X + 8,  CENTER_Y - 2}},
        {"l", {CENTER_X + 10, CENTER_Y - 2}},
        {"m", {CENTER_X + 12, CENTER_Y - 2}},
        {"n", {CENTER_X - 12, CENTER_Y}},
        {"o", {CENTER_X - 10, CENTER_Y}},
        {"p", {CENTER_X - 8,  CENTER_Y}},
        {"q", {CENTER_X - 6,  CENTER_Y}},
        {"r", {CENTER_X - 4,  CENTER_Y}},
        {"s", {CENTER_X - 2,  CENTER_Y}},
        {"t", {CENTER_X,      CENTER_Y}},
        {"u", {CENTER_X + 2,  CENTER_Y}},
        {"v", {CENTER_X + 4,  CENTER_Y}},
        {"w", {CENTER_X + 6,  CENTER_Y}},
        {"x", {CENTER_X + 8,  CENTER_Y}},
        {"y", {CENTER_X + 10, CENTER_Y}},
        {"z", {CENTER_X + 12, CENTER_Y}},
        {"0", {CENTER_X - 12, CENTER_Y + 2}},
        {"1", {CENTER_X - 10, CENTER_Y + 2}},
        {"2", {CENTER_X - 8,  CENTER_Y + 2}},
        {"3", {CENTER_X - 6,  CENTER_Y + 2}},
        {"4", {CENTER_X - 4,  CENTER_Y + 2}},
        {"5", {CENTER_X - 2,  CENTER_Y + 2}},
        {"6", {CENTER_X,      CENTER_Y + 2}},
        {"7", {CENTER_X + 2,  CENTER_Y + 2}},
        {"8", {CENTER_X + 4,  CENTER_Y + 2}},
        {"9", {CENTER_X + 6,  CENTER_Y + 2}},
    };

    static const std::vector<std::pair<std::string, std::pair<int, int>>> buttonMap =
    {
        {"save",   {CENTER_X - 8, CENTER_Y + 8}},
        {"delete", {CENTER_X + 8, CENTER_Y + 8}},
    };

    static auto start = std::chrono::system_clock::now();
    static bool animate = false;
    auto end = std::chrono::system_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (ms >= 200)
    {
        start = std::chrono::system_clock::now();
        animate = !animate;
    }

    writeCenteredStringOnMap(CENTER_X, CENTER_Y - 6, _playerName);

    for (const auto & alphabet : alphabetMap)
    {
        if (_namePanelCursorString == alphabet.first && !animate)
            writeCenteredStringOnMap(alphabet.second.first, alphabet.second.second,
                ">" + alphabet.first + "<");
        else
            writeCenteredStringOnMap(alphabet.second.first, alphabet.second.second, alphabet.first);
    }

    for (const auto & button : buttonMap)
    {
        if (_namePanelCursorString == button.first && !animate)
            writeCenteredStringOnMap(button.second.first, button.second.second,
                ">" + button.first + "<");
        else
            writeCenteredStringOnMap(button.second.first, button.second.second, button.first);
    }
}

void PacMan::updateName()
{
    clearMap();
    interactionsNamePanel();
    drawNamePanel();
}