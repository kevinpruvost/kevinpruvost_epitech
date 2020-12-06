/*
** A Kevin Pruvost's project, May 2020
** MainWindow.cpp
** File description:
** ma
*/

#include "MainWindow.hpp"

static std::mutex mutex;

MainWindow::MainWindow(int ac, char ** av)
    : _window(sf::VideoMode(1000, 800), "Le chat graphique",
      sf::Style::Titlebar | sf::Style::Close)
    , client(ac, av)
{
    _textures.emplace_back();
    _textures.back().loadFromFile("./resources/chat.png");
    _sprites.emplace_back(_textures.back());

    font.loadFromFile("./resources/tahoma.TTF");

    _usersText.setFont(font);
    _inputText.setFont(font);
    _msgText.setFont(font);

    _usersText.setCharacterSize(15);
    _inputText.setCharacterSize(15);
    _msgText.setCharacterSize(15);

    _usersText.setPosition(530, 70);
    _inputText.setPosition(20, 765);
    _msgText.setPosition(23, 47);

    _usersText.setString("");
    _inputText.setString("");
    _msgText.setString("");
}

MainWindow::~MainWindow()
{
}

std::string MainWindow::getChar()
{
    std::string c;
    const std::map<sf::Keyboard::Key, KVector<std::string>> chars = {
        {sf::Keyboard::Key::A, {{'a'}, {'A'}}},
        {sf::Keyboard::Key::B, {{'b'}, {'B'}}},
        {sf::Keyboard::Key::C, {{'c'}, {'C'}}},
        {sf::Keyboard::Key::D, {{'d'}, {'D'}}},
        {sf::Keyboard::Key::E, {{'e'}, {'E'}}},
        {sf::Keyboard::Key::F, {{'f'}, {'F'}}},
        {sf::Keyboard::Key::G, {{'g'}, {'G'}}},
        {sf::Keyboard::Key::H, {{'h'}, {'H'}}},
        {sf::Keyboard::Key::I, {{'i'}, {'I'}}},
        {sf::Keyboard::Key::J, {{'j'}, {'J'}}},
        {sf::Keyboard::Key::K, {{'k'}, {'K'}}},
        {sf::Keyboard::Key::L, {{'l'}, {'L'}}},
        {sf::Keyboard::Key::M, {{'m'}, {'M'}}},
        {sf::Keyboard::Key::N, {{'n'}, {'N'}}},
        {sf::Keyboard::Key::O, {{'o'}, {'O'}}},
        {sf::Keyboard::Key::P, {{'p'}, {'P'}}},
        {sf::Keyboard::Key::Q, {{'q'}, {'Q'}}},
        {sf::Keyboard::Key::R, {{'r'}, {'R'}}},
        {sf::Keyboard::Key::S, {{'s'}, {'S'}}},
        {sf::Keyboard::Key::T, {{'t'}, {'T'}}},
        {sf::Keyboard::Key::U, {{'u'}, {'U'}}},
        {sf::Keyboard::Key::V, {{'v'}, {'V'}}},
        {sf::Keyboard::Key::W, {{'w'}, {'W'}}},
        {sf::Keyboard::Key::X, {{'x'}, {'X'}}},
        {sf::Keyboard::Key::Y, {{'y'}, {'Y'}}},
        {sf::Keyboard::Key::Z, {{'z'}, {'Z'}}},
        {sf::Keyboard::Key::Num0, {{"à"}, {'0'}}},
        {sf::Keyboard::Key::Num1, {{'&'}, {'1'}}},
        {sf::Keyboard::Key::Num2, {{"é"}, {'2'}}},
        {sf::Keyboard::Key::Num3, {{'"'}, {'3'}}},
        {sf::Keyboard::Key::Num4, {{'\''}, {'4'}}},
        {sf::Keyboard::Key::Num5, {{'('}, {'5'}}},
        {sf::Keyboard::Key::Num6, {{'-'}, {'6'}}},
        {sf::Keyboard::Key::Num7, {{"è"}, {'7'}}},
        {sf::Keyboard::Key::Num8, {{'_'}, {'8'}}},
        {sf::Keyboard::Key::Num9, {{"ç"}, {'9'}}},
        {sf::Keyboard::Key::Numpad0, {{'0'}, {'0'}}},
        {sf::Keyboard::Key::Numpad1, {{'1'}, {'1'}}},
        {sf::Keyboard::Key::Numpad2, {{'2'}, {'2'}}},
        {sf::Keyboard::Key::Numpad3, {{'3'}, {'3'}}},
        {sf::Keyboard::Key::Numpad4, {{'4'}, {'4'}}},
        {sf::Keyboard::Key::Numpad5, {{'5'}, {'5'}}},
        {sf::Keyboard::Key::Numpad6, {{'6'}, {'6'}}},
        {sf::Keyboard::Key::Numpad7, {{'7'}, {'7'}}},
        {sf::Keyboard::Key::Numpad8, {{'8'}, {'8'}}},
        {sf::Keyboard::Key::Numpad9, {{'9'}, {'9'}}},
        {sf::Keyboard::Key::Divide, {{'/'}, {'/'}}},
        {sf::Keyboard::Key::Slash, {{'/'}, {'/'}}},
        {sf::Keyboard::Key::LBracket, {{'['}, {'['}}},
        {sf::Keyboard::Key::RBracket, {{']'}, {']'}}},
        {sf::Keyboard::Key::SemiColon, {{';'}, {';'}}},
        {sf::Keyboard::Key::Comma, {{','}, {','}}},
        {sf::Keyboard::Key::Period, {{'.'}, {'.'}}},
        {sf::Keyboard::Key::Quote, {{'\''}, {'\''}}},
        {sf::Keyboard::Key::BackSlash, {{'\\'}, {'\\'}}},
        {sf::Keyboard::Key::Tilde, {{'~'}, {'~'}}},
        {sf::Keyboard::Key::Equal, {{'='}, {'='}}},
        {sf::Keyboard::Key::Dash, {{'-'}, {'-'}}},
        {sf::Keyboard::Key::Space, {{' '}, {' '}}}
    };

    if (_event.type == sf::Event::KeyReleased)
    {
        try
        {
            int index = (_event.key.shift) ? 1 : 0;
            c = chars.at(_event.key.code)[index];
        }
        catch(const std::exception& e) {}
    }
    return c;
}

void MainWindow::drawUsers()
{
    std::string msgStr;
    size_t lineSize = 0;
    size_t lineCount = 1;

    for (const auto & user : client._users)
    {
        msgStr += user.name + "\t[" + user.uuid + "]\n";
    }

    for (size_t i = 0; i < msgStr.size(); ++i)
    {
        if (msgStr[i] == '\n')
        {
            lineSize = 0;
            ++lineCount;
        }
        if (lineSize >= 80)
            msgStr.insert(i, "\n");
        ++lineSize;
    }
    while (lineCount > 39)
    {
        msgStr = msgStr.substr(msgStr.find("\n") + 1);
        --lineCount;
    }
    _usersText.setString(msgStr);
}

void MainWindow::drawMsg()
{
    auto str = client.getDisplay();
    if (!str.empty())
    {
        auto msgStr = _msgText.getString();
        msgStr += str + "\n";
        size_t lineSize = 0;
        size_t lineCount = 1;
        for (size_t i = 0; i < msgStr.getSize(); ++i)
        {
            if (msgStr[i] == '\n')
            {
                lineSize = 0;
                ++lineCount;
            }
            if (lineSize >= 80)
                msgStr.insert(i, "\n");
            ++lineSize;
        }

        while (lineCount > 39)
        {
            msgStr = msgStr.substring(msgStr.find("\n") + 1);
            --lineCount;
        }

        _msgText.setString(msgStr);
    } // 39 lignes max
}

void MainWindow::chatPanel()
{
    auto c = getChar();

    if (!c.empty() && _inputText.getString().getSize() < 105)
    {
        _inputText.setString(_inputText.getString() + c);
    }

    if (_event.type == sf::Event::KeyReleased)
    {
        if (_inputText.getString().getSize() != 0)
            if (_event.key.code == sf::Keyboard::Delete || _event.key.code == sf::Keyboard::BackSpace)
                _inputText.setString(_inputText.getString().substring(0, _inputText.getString().getSize() - 1));

        if (_event.key.code == sf::Keyboard::Return)
        {
            client.launchCommand(_inputText.getString());
            _inputText.setString("");
        }
        _event.type = sf::Event::Count;
    }

    drawUsers();
    drawMsg();

    for (const auto & sprite : _sprites)
        _window.draw(sprite);
    _window.draw(_usersText);
    _window.draw(_inputText);
    _window.draw(_msgText);
}

int MainWindow::exec()
{
    if (!client.connected)
    {
        std::unique_lock<std::mutex> lock(mutex);
        client.condConnected.wait_for(lock, std::chrono::seconds(1));
        if (!client.connected)
        {
            std::cout << "Could not connect to the server." << std::endl;
            return EXIT_FAILURE;
        }
    }

    while (_window.isOpen() && !stop_the_program(false))
    {
        while (_window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear();

        chatPanel();

        _window.display();
    }

    _window.close();

    return EXIT_SUCCESS;
}