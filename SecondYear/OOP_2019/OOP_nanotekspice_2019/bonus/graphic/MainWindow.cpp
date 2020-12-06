/*
** EPITECH PROJECT, 2020
** MainWindow.cpp
** File description:
** main window
*/

#include "MainWindow.hpp"

MainWindow::MainWindow(const int ac, const char ** av)
    : argc { ac }
    , argv { av }
{
}

MainWindow::~MainWindow()
{
}

int MainWindow::exec()
{
    if (argc < 2)
        return EXIT_FAILURE;

    nts::Circuit c;
    Parser p(argv[1], c);
    if (!p.parse())
        return EXIT_FAILURE;
    AddValue a(argv, c);
    if (!a.parse())
        return EXIT_FAILURE;
    Shell s(c);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "NanoGrekSpice", sf::Style::Titlebar | sf::Style::Close);
    sf::Texture background;
    background.loadFromFile(Constants::backgroundPath);
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(background);
    backgroundSprite.setScale(WINDOW_WIDTH / backgroundSprite.getTextureRect().width,
                              WINDOW_HEIGHT / backgroundSprite.getTextureRect().height);

    while (window.isOpen())
    {
        while (window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(backgroundSprite);

        drawCircuit(window, c.getComponents());

        window.display();
        if (!s.takeCommand())
            window.close();
    }
    return EXIT_SUCCESS;
}

// drawCircuit -----------------------------------------------------------------

void MainWindow::drawCircuit(sf::RenderWindow & window,
    const std::vector<std::unique_ptr<nts::IComponent>> & comps)
{
    if (_gcomps.empty())
    {
        for (const auto & comp : comps)
        {
            bool found = false;
            if (!found)
                _gcomps.push_back(GComponent(*comp));
        }

        sf::Vector2f inputPos(64, 64);
        sf::Vector2f componentPos(384, 64);
        sf::Vector2f outputPos(704, 64);
        for (auto & gcomp : _gcomps)
        {
            if (gcomp._comp.getComponentType() == nts::ComponentType::INPUT)
            {
                gcomp._sprite.setPosition(inputPos);
                inputPos.y -= 12;
                inputPos.x += 8;
                gcomp._name.setPosition(inputPos);
                inputPos.x -= 8;
                inputPos.y += 62;
            }
            if (gcomp._comp.getComponentType() == nts::ComponentType::COMPONENT)
            {
                gcomp._sprite.setPosition(componentPos);
                componentPos.y -= 12;
                componentPos.x += 16;
                gcomp._name.setPosition(componentPos);
                componentPos.x -= 16;
                componentPos.y += 92;
            }
            if (gcomp._comp.getComponentType() == nts::ComponentType::OUTPUT)
            {
                gcomp._sprite.setPosition(outputPos);
                outputPos.y -= 12;
                outputPos.x += 12;
                gcomp._name.setPosition(outputPos);
                outputPos.x -= 12;
                outputPos.y += 62;
            }
        }
    }
    else
    {
        for (auto & gcomp : _gcomps)
            gcomp.refresh();
    }
    

    for (const auto & gcomp : _gcomps)
    {
        window.draw(gcomp._sprite);
        window.draw(gcomp._name);
    }
}