/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** MainPage
*/

#include "MainPage.hpp"

using namespace RType::Client::Rendering;

MainPage::MainPage()
{
}

MainPage::~MainPage()
{
    _window.close();
}

void MainPage::Start()
{
    _window.create(sf::VideoMode(800, 600), "RType");
    while (1) {}
}
