/*
** A Kevin Pruvost's project, May 2020
** Page.hpp
** File description:
** page
*/

#pragma once

// Project includes
#include "IPage.hpp"

class Page : virtual public IPage
{
public:
    enum PageId
    {
        NONE,
        MENU,
        GAME
    };

    Page(sf::RenderWindow & window, sf::Event & event, SfmlIpc &);
    ~Page();

    virtual int exec() = 0;
    virtual void event(int &, bool &) = 0;
    std::vector<std::unique_ptr<Kitchen>> getKitchens();
    std::vector<Pizza> getPizzas();
    void addPizza(const Pizza & pizza);
    void addPizza(Pizza::PizzaType type, Pizza::PizzaSize size);
    void closeAll();

protected:
    void changePage(Page::PageId id);
    int getPageChange() { return _pageChange; }

protected:
    PageId _pageChange = NONE;
    sf::RenderWindow & _window;
    sf::Event & _event;
    SfmlIpc & _ipc;

private:
};