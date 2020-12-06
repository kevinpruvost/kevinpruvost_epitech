/*
** EPITECH PROJECT, 2020
** Shell.cpp
** File description:
** shell
*/

#include "Shell.hpp"

std::mutex mutex;

static void signalHandler(int sig)
{
    if (sig == SIGINT)
    {
        workingProcess = false;
        write(STDIN_FILENO, "\0", 1);
        close(STDIN_FILENO);
        return;
    }
}

Shell::Shell(Manager & manager)
    : _manager { manager }
{
    signal(SIGINT, signalHandler);
}

Shell::~Shell()
{
}

void Shell::displayKitchensStatus()
{
    auto & kitchens = _manager.getStatus();
    size_t i = 1;
    std::map<Ingredient::IngredientType, std::string> ingredient_types = {{Ingredient::DOE, "Doe"}, {Ingredient::TOMATO, "Tomato"},
                                                {Ingredient::GRUYERE, "Gruyere"}, {Ingredient::HAM, "Ham"},
                                                {Ingredient::MUSHROOMS, "Mushrooms"}, {Ingredient::STEAK, "Steak"},
                                                {Ingredient::EGGPLANT, "Eggplant"}, {Ingredient::GOAT_CHEESE, "Goat cheese"},
                                                {Ingredient::CHIEF_LOVE, "Chief love"}};
    std::map<Ingredient::IngredientType, unsigned int> ingredients;
    std::vector<std::shared_ptr<Pizza>> pizzas;

    std::cerr << "\033[1;4;32mThe restaurant has " << kitchens.size() << " running kitchens.\n\033[0m" << std::endl;
    for (auto & kitchen : kitchens) {
        size_t j = 0;
        std::cerr << " \033[1;32mKitchen n°" << i << ":\033[0m" << std::endl;
        ingredients = kitchen->getStock().getIngredients();
        std::cerr << "  \033[1;33mPrinting stocks:" << std::endl;
        unsigned int k = 0;
        for (auto & ingredient : ingredients) {
            std::cerr << ((k == 0) ? "   -" : "") << ingredient_types.at(ingredient.first) << " " << ingredient.second;
            if (k != ingredients.size() - 1)
                std::cerr << ((k != 0 && (k + 1) % 3 == 0) ? "\n   -" : "\t") << std::flush;
            ++k;
        }
        std::cerr << "\033[0m\n  \033[1;35mThe kitchen is" << (kitchen->isWorking() ? "" : " not") << " working.\033[0m" << std::endl;
        pizzas = kitchen->getPizzas();
        std::cerr << "  \033[1;37mPreparing pizzas:" << std::endl;
        std::cerr << "   [";
        for (std::shared_ptr<Pizza> pizza : pizzas) {
            if (j != 0)
                std::cerr << ", ";
            std::cerr << CreateStringFromPizzas(*pizza.get());
            ++j;
        }
        std::cerr << "]\033[0m" << std::endl << std::endl;
        ++i;
    }
}

bool isNum(std::string str)
{
    for (char c : str) {
        if (c < '0' || '9' < c)
            return (false);
    }
    return (true);
}

static int myReadStdin(std::string & str)
{
    static std::string rest;
    char buffer[8192];
    int ret = 8192;

	if (rest.find('\n') != std::string::npos)
    {
        str = rest.substr(0, rest.find_first_of('\n'));
        rest = rest.substr(rest.find_first_of('\n') + 1);
		if (rest.find_first_of('\n') == rest.size() - 1)
			rest.clear();
        return str.size() + 1;
    }
    str = rest;
	rest.clear();
    while (ret == 8192)
    {
        memset(buffer, 0, 8192);
        ret = read(STDIN_FILENO, buffer, 8192);
        if (ret <= 0)
            break;
        str += buffer;
        if (str.find('\n') != std::string::npos)
        {
            rest = str.substr(str.find_first_of('\n') + 1);
            str = str.substr(0, str.find_first_of('\n'));
            break;
        }
    }
    return ret;
}

int Shell::exec()
{
    std::string str;
    std::smatch match;
    std::vector<std::string> params;
    std::regex reg("\\w+\\s+(S|M|L|XL|XXL)\\s+x\\d+");
    std::string pizz_order;
    std::map<std::string, Pizza::PizzaType> pizz_types = {{"regina", Pizza::Regina}, {"margarita", Pizza::Margarita},
                                                          {"americana", Pizza::Americana}, {"fantasia", Pizza::Fantasia}};
    std::map<std::string, Pizza::PizzaSize> pizz_sizes = {{"S", Pizza::S}, {"M", Pizza::M},
                                                          {"L", Pizza::L}, {"XL", Pizza::XL},
                                                          {"XXL", Pizza::XXL}};

    std::cerr << "\nWelcome to the 'Des Freds et des Fourchettes' plazza, the best of Italy just for you !\n"
                 "Commands :\n  -Pizza Ordering :\tregina|fantasia|margarita|americana S|M|L|XL|XXL x{PIZZA_NUMBER}\n"
                 "  -Status :\t\tstatus\n"
              << std::endl;
    while (workingProcess) {
        std::cerr << ">";
        if (myReadStdin(str) <= 0)
            break;
        if (str == "exit") {
            std::cerr << "Waiter: A presto !" << std::endl;
            kill(getpid(), SIGINT);
            break;
        } else if (std::regex_search(str, match, reg)) {
            while (std::regex_search(str, match, reg)) {
                pizz_order = match.str(0);
                pizz_order = std::regex_replace(pizz_order, (std::regex)"\\s+", " ");
                params.clear();
                splitToArray(pizz_order, params, " ");
                if (params.size() < 3)
                    break;
                params.at(2) = std::regex_replace(params.at(2), (std::regex)"x", "");
                if (!isPizzaTypeValid(params.at(0)) || !isNum(params.at(2))) {
                    std::cerr << "Waiter: Non conosco questa pizza!" << std::endl;
                    break;
                }
                std::cerr << "Waiter: You ordered " << params[2] << " " << params[0] << " " << params[1] << std::endl;
                this->_manager.createNewPizza(pizz_types[params.at(0)], pizz_sizes[params.at(1)], std::stoi(params.at(2)));
                if (isChildProcess)
                    return EXIT_SUCCESS;
                str = match.suffix().str();
            }
        } else if (str == "status") {
            displayKitchensStatus();
        } else {
            std::cerr << "Waiter: no comprendo" << std::endl;
        }
    }
    workingProcess = false;
    return (EXIT_SUCCESS);
}