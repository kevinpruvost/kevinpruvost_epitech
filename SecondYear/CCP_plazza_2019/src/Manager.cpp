/*
** EPITECH PROJECT, 2020
** Manager.cpp
** File description:
** manager
*/

#include "Manager.hpp"

static std::mutex mutex;
static std::condition_variable cond;
static bool ready = true;

Manager::Manager(double cookingTimeMultiplier, int cooksPerKitchen, int replaceTimeIngredients)
    : _cookingTimeMultiplier  { cookingTimeMultiplier  }
    , _cooksPerKitchen        { cooksPerKitchen        }
    , _replaceTimeIngredients { replaceTimeIngredients }
{
}

Manager::~Manager()
{
}

std::vector<std::shared_ptr<Kitchen>> & Manager::getStatus()
{
    while (!ready)
    {
        std::cout << "Getting status..." << std::endl;
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock);
    }
    return _kitchens;
}

void Manager::createNewKitchens()
{
    _kitchens.push_back(std::shared_ptr<Kitchen> \
{std::make_shared<Kitchen>(_cooksPerKitchen, _cookingTimeMultiplier)});
}

std::vector<int> Manager::findLazyKitchen(int size)
{
    int lazy = 0;
    int length = 0;
    std::vector<int> laziVector;
    std::vector<std::pair<double, int>> cookingTime;
    double lowestCookingTime = 0;
    int i = 0;

    for (auto & kitchen : _kitchens)
        length += (_cooksPerKitchen * NBR_PIZZA_PER_COOK) - kitchen.get()->getPizzas().size();

    while (size > length) {
        createNewKitchens();
        if (isChildProcess)
            return laziVector;
        length += (_cooksPerKitchen * NBR_PIZZA_PER_COOK);
    }

    std::vector<int> ban(_kitchens.size(), 0);

    for (auto & kitchen : _kitchens) {
        auto & allPizzaPerKitchen = kitchen.get()->getPizzas();
        int sizeKitchen = (int)allPizzaPerKitchen.size();
        ban[i] = sizeKitchen;
        lowestCookingTime = 0;
        for (auto & pizzaList : allPizzaPerKitchen)
            lowestCookingTime += pizzaList->getCookingTime();
        cookingTime.push_back(std::pair<double, int>{lowestCookingTime, i});
        ++i;
    }
    int j = 0;

    for (int i = 0; i < size; ++i) {
        lazy = 0;
        j = 0;
        for (auto & l : cookingTime) {
            if (j == 0) {
                lowestCookingTime = l.first;
                lazy = l.second;
                ++j;
                ban[l.second] += 1;
            }
            if (l.first <= lowestCookingTime && ban[l.second] < (_cooksPerKitchen * 2)) {
                lowestCookingTime = l.first;
                ban[lazy] -= 1;
                ban[l.second] += 1;
                lazy = l.second;
            }
        }
        laziVector.push_back(lazy);
    }
    return laziVector;
}

void Manager::createNewPizza(Pizza::PizzaType type, Pizza::PizzaSize size, int number)
{
    for (int i = 0; i < number; ++i)
    {
        _newPizza.push_back(PizzaFactory::createSharedPizza(type, size));
        _pizzaMemory.emplace_back(_newPizza.back());
    }

    while (!ready)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock);
    }
    ready = false;
    std::vector<int> container = findLazyKitchen(number);
    if (isChildProcess)
        return;
    ready = true;
    cond.notify_all();


    while ((int)container.size() != 0) {
        std::vector<std::shared_ptr<Pizza>> give;
        int p = container.front();
        for (int o = 0; o < (int)container.size();) {
            if (p == container[o]) {
                give.push_back(_newPizza[o]);
                container.erase(container.begin() + o);
            } else
                ++o;
        }
        if (give.size() > 0)
            _kitchens[p].get()->addPizzas(give);
    }

    for (const auto & kitchen : _kitchens)
        kitchen->beginAfk();

    _newPizza.clear();
}

void Manager::inactif()
{
    while (!ready)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock);
    }
    for (unsigned int k = 0; k < _kitchens.size(); ++k) {
        auto & i = _kitchens[k];
        if (!i.get()->isWorking()) {
            if (i->afkTime() >= INACTIVE_TIME)
            {
                ready = false;
                i->kill();
                _kitchens.erase(_kitchens.begin() + k);
                --k;
                ready = true;
                cond.notify_all();
            }
        }
    }
}

void Manager::resetStock()
{
    while (workingProcess)
    {
        while (!ready)
        {
            std::unique_lock<std::mutex> lock(mutex);
            cond.wait(lock);
        }
        ready = false;
        for (auto & kitchen : _kitchens)
            kitchen.get()->restock();
        ready = true;
        cond.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(_replaceTimeIngredients));
    }
}

int Manager::exec()
{
    std::shared_ptr<std::thread> stockManagement(std::make_shared<std::thread>(&Manager::resetStock, this));
    stockManagement->detach();

    while (workingProcess)
    {
        inactif();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return EXIT_SUCCESS;
}

const std::vector<std::shared_ptr<Kitchen>> & Manager::getKitchens() const
{
    while (!ready)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock);
    }
    return _kitchens;
}

const std::vector<std::shared_ptr<Pizza>> & Manager::getPizzas() const
{
    return _pizzaMemory;
}