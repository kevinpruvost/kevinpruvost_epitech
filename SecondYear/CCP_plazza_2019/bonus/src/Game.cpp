/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Game
*/

#include "Game.hpp"

#define NB_COOKS 2

Game::Game(sf::RenderWindow & window, sf::Event & event, SfmlIpc & ipc)
    : Page(window, event, ipc), _pizza_textures(NB_PIZZA_BTNS), _views(NB_VIEWS), _rectangles(NB_RECTANGLES), _pizzaBtns(NB_PIZZA_BTNS), _texts(NB_TEXTS)
{
    _windowSize = (sf::Vector2f)_window.getSize();

    _pizza_textures.at(PIZZAS_BTNS::REGINA).loadFromFile("./bonus/resources/regina.png");
    _pizza_textures.at(PIZZAS_BTNS::MARGARITA).loadFromFile("./bonus/resources/margarita.png");
    _pizza_textures.at(PIZZAS_BTNS::AMERICANA).loadFromFile("./bonus/resources/americana.png");
    _pizza_textures.at(PIZZAS_BTNS::FANTASIA).loadFromFile("./bonus/resources/fantasia.png");

    _rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first.setPosition(sf::Vector2f(0, 0));
    _rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first.setSize(sf::Vector2f(170, 170));
    _rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first.setFillColor(sf::Color::White);
    _rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first.setOutlineColor(sf::Color::Black);
    _rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first.setOutlineThickness(2);

    _rectangles.at(RECTANGLES::PIZZA).first.setPosition(sf::Vector2f(0, 0));
    _rectangles.at(RECTANGLES::PIZZA).first.setSize(sf::Vector2f(40, 40));
    _rectangles.at(RECTANGLES::PIZZA).first.setTexture(&_pizza_textures.at(PIZZAS_BTNS::REGINA));
    _rectangles.at(RECTANGLES::PIZZA).first.setOutlineColor(sf::Color::Black);
    _rectangles.at(RECTANGLES::PIZZA).first.setOutlineThickness(2);
    
    _rectangles.at(RECTANGLES::PIZZA_BACKGROUND).first.setPosition(sf::Vector2f(0, _windowSize.y * 0.75));
    _rectangles.at(RECTANGLES::PIZZA_BACKGROUND).first.setSize(sf::Vector2f(_windowSize.x, _windowSize.y * 0.25));
    _rectangles.at(RECTANGLES::PIZZA_BACKGROUND).first.setFillColor(sf::Color(211, 84, 0, 200));
    _rectangles.at(RECTANGLES::PIZZA_BACKGROUND).first.setOutlineColor(sf::Color(30, 30, 30, 200));
    _rectangles.at(RECTANGLES::PIZZA_BACKGROUND).first.setOutlineThickness(5);

    _pizzaBtns.at(PIZZAS_BTNS::REGINA).first.setTexture(&_pizza_textures.at(PIZZAS_BTNS::REGINA));
    _pizzaBtns.at(PIZZAS_BTNS::MARGARITA).first.setTexture(&_pizza_textures.at(PIZZAS_BTNS::MARGARITA));
    _pizzaBtns.at(PIZZAS_BTNS::AMERICANA).first.setTexture(&_pizza_textures.at(PIZZAS_BTNS::AMERICANA));
    _pizzaBtns.at(PIZZAS_BTNS::FANTASIA).first.setTexture(&_pizza_textures.at(PIZZAS_BTNS::FANTASIA));

    sf::Vector2f btn_pos(0.25, 0.78);
    for (size_t i = 0; i < NB_PIZZA_BTNS; ++i) {
        _pizzaBtns.at(i).first.setPosition(sf::Vector2f(_windowSize.x * btn_pos.x, _windowSize.y * btn_pos.y));
        _pizzaBtns.at(i).first.setSize(sf::Vector2f(200, 200));
        _pizzaBtns.at(i).first.setOutlineThickness(4);
        _pizzaBtns.at(i).first.setOutlineColor(sf::Color(200, 200, 200));
        btn_pos.x += 0.15f;
    }

    _laFont.loadFromFile("./bonus/resources/panpizza.ttf");

    _texts.at(TEXTS::INFO_INPUTS).setFont(_laFont);
    _texts.at(TEXTS::INFO_INPUTS).setCharacterSize(40);
    _texts.at(TEXTS::INFO_INPUTS).setFillColor(sf::Color::White);
    _texts.at(TEXTS::INFO_INPUTS).setPosition(sf::Vector2f(_windowSize.x * 0.05, _windowSize.y * 0.78));
    _texts.at(TEXTS::INFO_INPUTS).setString("In-game shortcuts:\n-ZQSD: Move around\n-AE: Zoom/Dezoom\nHold MB1: Move around with mouse");

    _views.at(VIEWS::DEFAULT) = _window.getView();

    _views.at(VIEWS::KITCHENS).reset(sf::FloatRect(0, 0, _window.getSize().x, _window.getSize().y));
    _views.at(VIEWS::KITCHENS).setViewport(sf::FloatRect(0, 0, 1, 1));

    _lastMousePos.x = -100;
}

Game::~Game() { closeAll(); }

double getPizzaSize(double x, double y, double n){
    double px = ceil(sqrt(n * x / y));
    double sx, sy;

    if (floor(px * y / x) * px < n)  //does not fit, y/(x/px)=px*y/x
        sx = y / ceil(px * y / x);
    else
        sx = x / px;
    double py = ceil(sqrt(n * y / x));
    if (floor(py * x / y) * py < n)  //does not fit
        sy = x / ceil(x * py / y);
    else
        sy = y / py;
    return MAX(sx, sy);
}

size_t Game::getTextureIdx(Pizza::PizzaType type)
{
    switch (type) {
        case Pizza::PizzaType::Regina: return (0);
            break;
        case Pizza::PizzaType::Margarita: return (1);
            break;
        case Pizza::PizzaType::Americana: return (2);
            break;
        case Pizza::PizzaType::Fantasia: return (3);
            break;
        default: return (0);
            break;
    }
}

Pizza::PizzaType Game::getPizzaBtnType(size_t btnIdx)
{
    switch (btnIdx) {
        case 0: return (Pizza::PizzaType::Regina);
        break;
        case 1: return (Pizza::PizzaType::Margarita);
        break;
        case 2: return (Pizza::PizzaType::Americana);
        break;
        case 3: return (Pizza::PizzaType::Fantasia);
        break;
        default: return (Pizza::PizzaType::Regina);
        break;
    }
}

int Game::exec()
{
    sf::Vector2f kitchen_pos(2, 2);
    sf::Vector2f pizza_pos(0, 0);

    sf::Vector2f kitchen_size = _rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first.getSize();

    size_t nb_pizzas;

    auto kitchens = Page::getKitchens();
    std::vector<std::shared_ptr<Pizza>> pizzas;

    _window.setView(_views.at(VIEWS::KITCHENS));

    //_window.draw(_rectangles.at(RECTANGLES::BACKGROUND).first);
    for (std::unique_ptr<Kitchen> & kitchen : kitchens) {
        pizzas = kitchen->getPizzas();
        nb_pizzas = pizzas.size();

        double test = getPizzaSize(kitchen_size.x, kitchen_size.y, nb_pizzas);
        sf::Vector2f pizza_size = sf::Vector2f(test - 4, test - 4);
        _rectangles.at(RECTANGLES::PIZZA).first.setSize(pizza_size);
        /* KITCHEN DISPLAY */
        _rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first.setFillColor((kitchen->afkTime() <= 2000 ? sf::Color::Green : (kitchen->afkTime() <= 4000 ? sf::Color::Yellow : sf::Color::Red)));
        _rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first.setPosition(kitchen_pos);
        _window.draw(_rectangles.at(RECTANGLES::KITCHEN_BACKGROUND).first);

        /* PIZZA DISPLAY */
        pizza_pos = kitchen_pos;
        pizza_pos.x += 2;
        pizza_pos.y += 2;
        for (size_t i = 0; i < nb_pizzas; ++i) {
            _rectangles.at(RECTANGLES::PIZZA).first.setPosition(pizza_pos);
            _rectangles.at(RECTANGLES::PIZZA).first.setTexture(&_pizza_textures.at(getTextureIdx(pizzas.at(i)->getPizzaType())));
            _window.draw(_rectangles.at(RECTANGLES::PIZZA).first);
            pizza_pos.x += pizza_size.x + 4;
            if (pizza_pos.x > (kitchen_pos.x + kitchen_size.x) - pizza_size.x) {
                pizza_pos.x = kitchen_pos.x + 2;
                pizza_pos.y += pizza_size.y + 4;
            }
        }
        kitchen_pos.x += kitchen_size.x + 4;
        if (kitchen_pos.x > _windowSize.x - kitchen_size.x) {
            kitchen_pos.x = 2;
            kitchen_pos.y += kitchen_size.y + 4;
        }
    }

    /* UI */
    _window.setView(_views.at(VIEWS::DEFAULT));
    _window.draw(_rectangles.at(RECTANGLES::PIZZA_BACKGROUND).first);
    for (size_t i = 0; i < NB_TEXTS; i++)
        _window.draw(_texts.at(i));
    for (size_t i = 0; i < NB_PIZZA_BTNS; ++i) {
        _window.draw(_pizzaBtns.at(i).first);
    }
    return EXIT_SUCCESS;
}

void Game::event(int & page, bool & workingProcess)
{
    if (_event.type == sf::Event::KeyPressed) {
        switch (_event.key.code) {
            case sf::Keyboard::Z: _views.at(VIEWS::KITCHENS).move(0, -50);
            break;
            case sf::Keyboard::Q: _views.at(VIEWS::KITCHENS).move(-50, 0);
            break;
            case sf::Keyboard::S: _views.at(VIEWS::KITCHENS).move(0, 50);
            break;
            case sf::Keyboard::D: _views.at(VIEWS::KITCHENS).move(50, 0);
            break;
            case sf::Keyboard::A: _views.at(VIEWS::KITCHENS).zoom(1.1f);
            break;
            case sf::Keyboard::E: _views.at(VIEWS::KITCHENS).zoom(0.9f);
            break;
            case sf::Keyboard::Escape: page = 0;
            break;
            default : break;
        }
    } else if (_event.type == sf::Event::MouseButtonPressed) {
        if (_event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(_window);

            for (size_t i = 0; i < NB_PIZZA_BTNS; ++i) {
                if (Game::isInBounds(mouse_pos, _pizzaBtns.at(i).first)) {
                    /* C ICI QUE LES PIZZAS SONT COMMANDÉES */
                    std::cout << "+New pizza ordered" << std::endl;
                    addPizza(Game::getPizzaBtnType(i), Pizza::PizzaSize::XXL);
                    return;
                }
            }
            if (_lastMousePos.x == -100) {
                _lastMousePos = sf::Mouse::getPosition(_window);
                _lastCenter = _views.at(VIEWS::KITCHENS).getCenter();
            }
        } else if (_event.mouseButton.button == sf::Mouse::Right) {
            //todo
        }
    } else if (_event.type == sf::Event::MouseButtonReleased) {
        if (_lastMousePos.x != -100)
            _lastMousePos.x = -100;
    } else if (_event.type == sf::Event::MouseMoved) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(_window);
        if (_lastMousePos.x != -100) {
            _views.at(VIEWS::KITCHENS).setCenter(_lastCenter.x + (_lastMousePos.x - mouse_pos.x), _lastCenter.y + (_lastMousePos.y - mouse_pos.y));
            return;
        }
        for (size_t i = 0; i < NB_PIZZA_BTNS; ++i) {
            if (Game::isInBounds(mouse_pos, _pizzaBtns.at(i).first)) {
                _pizzaBtns.at(i).first.setOutlineColor(sf::Color::Red);
            } else if (_pizzaBtns.at(i).first.getOutlineColor() != sf::Color::Transparent) {
                _pizzaBtns.at(i).first.setOutlineColor(sf::Color(200, 200, 200));
            }
        }
    }
}

bool Game::isInBounds(sf::Vector2i pos, sf::RectangleShape rectangle)
{
    sf::FloatRect bounds = rectangle.getGlobalBounds();

    return (bounds.left < pos.x && pos.x < bounds.left + bounds.width
            && bounds.top < pos.y && pos.y < bounds.top + bounds.height);
}