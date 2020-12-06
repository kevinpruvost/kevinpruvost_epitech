/*
** A Kevin Pruvost's project, May 2020
** SfmlIpc.cpp
** File description:
** sfmlipc
*/

#include "SfmlIpc.hpp"

static std::mutex mutex;

SfmlIpc::SfmlIpc()
    : Ipc()
{
    if (isChild())
    {
        _read.reset(new std::thread([&] {
            while (workingProcess)
            {
                //std::cout << "Child : le read est apellé" << std::endl;
                header_t * header = readBinary();
                if (!header)
                {
                    workingProcess = false;
                    break;
                }
                if (headerData)
                    headerData = nullptr;
                //std::cout << "Child : j'ai le header" << std::endl;
                std::unique_lock<std::mutex> lock(mutex);
                switch (header->command)
                {
                    case Command::GetPizzas:
                    {
                        headerData = header;
                        break;
                    }
                    case Command::GetKitchens:
                    {
                        headerData = header;
                        break;
                    }
                    case Command::AddPizza:
                    {
                        std::cout << "Pizza added to kitchens !" << std::endl;
                        break;
                    }
                    case Command::Exit:
                    {
                        write({Command::Exit, 0, nullptr});
                        workingProcess = false;
                        kill(getpid(), SIGINT);
                        break;
                    }
                    default:
                    {
                        workingProcess = false;
                        kill(getpid(), SIGINT);
                        break;
                    }
                };
                gotData = true;
                condGotData.notify_one();
            }
        }));
    }
    else
    {
        _read.reset(new std::thread([&] {
            while (workingProcess)
            {
                //std::cout << "Parent : le read a ete apellé" << std::endl;
                header_t * header = readBinary();
                if (!header)
                {
                    workingProcess = false;
                    break;
                }
                //std::cout << "Parent : j'ai le header" << std::endl;
                std::unique_lock<std::mutex> lock(mutex);
                switch (header->command)
                {
                    case Command::GetPizzas:
                    {
                        header_t head;
                        auto & pizzas = _plazza->getPizzas();
                        serializePizzaVector(pizzas, head);
                        head.command = Command::GetPizzas;
                        write(head);
                        free(head.buffer);
                        break;
                    }
                    case Command::GetKitchens:
                    {
                        header_t head;
                        auto & kitchens = _plazza->getKitchens();
                        serializeKitchenVector(kitchens, head);
                        head.command = Command::GetKitchens;
                        write(head);
                        break;
                    }
                    case Command::AddPizza:
                    {
                        auto pizza = deserializePizza(*header);
                        _plazza->manager.createNewPizza(pizza.getPizzaType(), pizza.getPizzaSize(), 1);
                        write({Command::AddPizza, 0, nullptr});
                        break;
                    }
                    case Command::Exit:
                    {
                        write({Command::Exit, 0, nullptr});
                        kill(getpid(), SIGINT);
                        workingProcess = false;
                        break;
                    }
                    default:
                    {
                        workingProcess = false;
                        kill(getpid(), SIGINT);
                        workingProcess = false;
                        break;
                    }
                };
                gotData = true;
                condGotData.notify_one();
            }
        }));
    }
    _read->detach();
}

SfmlIpc::~SfmlIpc()
{
    closeFds();
    workingProcess = false;
}

header_t SfmlIpc::getDataFromSentCommand()
{
    while (!gotData)
    {
        std::unique_lock<std::mutex> lock(mutex);
        condGotData.wait(lock);
    }
    gotData = false;
    if (!headerData)
        return {Command::Exit, 0, nullptr};
    return *headerData;
}

header_t SfmlIpc::getPizzas()
{
    if (isChild())
    {
        write({Command::GetPizzas, 0, nullptr});
        return getDataFromSentCommand();
    }
    else
        return {};
}

header_t SfmlIpc::getKitchens()
{
    if (isChild())
    {
        write({Command::GetKitchens, 0, nullptr});
        return getDataFromSentCommand();
    } else
        return {};
}

header_t SfmlIpc::addPizza(const Pizza & pizza)
{
    if (isChild())
    {
        header_t header = {Command::AddPizza, 0, nullptr};
        serializePizza(pizza, header);
        write(header);
        return getDataFromSentCommand();
    } else
        return {};
}

void SfmlIpc::exit()
{
    write({Command::Exit, 0, nullptr});
}

void SfmlIpc::serializeKitchenVector(const std::vector<std::shared_ptr<Kitchen>> & kitchens, header_t & header)
{
    header.size = 0;
    // afkTime, pizzasNumber, pizzas
    size_t dataSize = 0;
    for (const auto & kitchen : kitchens)
    {
        dataSize += sizeof(int); // afktime
        dataSize += sizeof(size_t); // pizzasNumber
        const auto & pizzas = kitchen->getPizzas();
        for (const auto & pizza : pizzas) // pizzas
        {
            UNUSED(pizza);
            dataSize += sizeof(Pizza::PizzaType);
            dataSize += sizeof(Pizza::PizzaSize);
            dataSize += sizeof(Pizza::PizzaState);
        }
    }
    header.buffer = malloc(dataSize);
    for (const auto & kitchen : kitchens)
    {
        const auto & pizzas = kitchen->getPizzas();
        int afkTime = kitchen->afkTime();
        memcpy((char *)header.buffer + header.size, &afkTime, sizeof(int)); //afkTime
        header.size += sizeof(int);
        size_t size = pizzas.size();
        memcpy((char *)header.buffer + header.size, &size, sizeof(size_t));
        header.size += sizeof(size_t);
        for (const auto & pizza : pizzas) // pizzas
        {
            auto type = pizza->getPizzaType();
            memcpy((char *)header.buffer + header.size, &type, sizeof(Pizza::PizzaType));
            header.size += sizeof(Pizza::PizzaType);
            auto siz = pizza->getPizzaSize();
            memcpy((char *)header.buffer + header.size, &siz, sizeof(Pizza::PizzaSize));
            header.size += sizeof(Pizza::PizzaSize);
            auto state = pizza->getState();
            memcpy((char *)header.buffer + header.size, &state, sizeof(Pizza::PizzaState));
            header.size += sizeof(Pizza::PizzaState);
        }
    }
}

std::vector<std::unique_ptr<Kitchen>> SfmlIpc::deserializeKitchenVector(header_t & header)
{
    std::vector<std::unique_ptr<Kitchen>> kitchens;

    size_t red = 0;
    void * data = header.buffer;
    while (red < header.size)
    {
        kitchens.push_back(std::make_unique<Kitchen>(0, 0, true));
        int afkTime;
        memcpy(&afkTime, (char *)data + red, sizeof(int));
        red += sizeof(int);
        size_t pizzasNumber;
        memcpy(&pizzasNumber, (char *)data + red, sizeof(size_t));
        red += sizeof(size_t);
        kitchens.back()->setAfkTime(afkTime);
        for (size_t i = 0; i < pizzasNumber; ++i)
        {
            Pizza::PizzaType type;
            memcpy(&type, (char *)data + red, sizeof(Pizza::PizzaType));
            red += sizeof(Pizza::PizzaType);
            Pizza::PizzaSize size;
            memcpy(&size, (char *)data + red, sizeof(Pizza::PizzaSize));
            red += sizeof(Pizza::PizzaSize);
            Pizza::PizzaState state;
            memcpy(&state, (char *)data + red, sizeof(Pizza::PizzaState));
            red += sizeof(Pizza::PizzaState);
            auto pizza = PizzaFactory::createPizza(type, size);
            pizza.setState(state);
            kitchens.back()->setPizza(Pizza(pizza));
        }
    }
    return kitchens;
}

void SfmlIpc::serializePizzaVector(const std::vector<std::shared_ptr<Pizza>> & pizzas, header_t & header)
{
    int datasize = 0;
    for (auto & cmp : pizzas)
    {
        UNUSED(cmp);
        header.size += (sizeof(int) * 4);
    }
    header.buffer = malloc(header.size);
    for (auto & cmp : pizzas) {
        size_t size = sizeof(int) * 3;
        memcpy((char*)header.buffer + datasize, &size, sizeof(size_t));
        datasize += sizeof(size_t);
        memcpy((char*)header.buffer + datasize, (void *)(cmp->getPizzaType()), sizeof(int));
        datasize += sizeof(int);
        memcpy((char*)header.buffer + datasize, (void *)(cmp->getPizzaSize()), sizeof(int));
        datasize += sizeof(int);
        memcpy((char*)header.buffer + datasize, (void *)(cmp->getState()), sizeof(int));
        datasize += sizeof(int);
    }
}

std::vector<Pizza> SfmlIpc::deserializePizzaVector(header_t & header)
{
    std::vector<Pizza> pizzas;
    size_t red = 0;
    while (red < header.size) {
        size_t limit;
        memcpy(&limit, (char*)header.buffer,sizeof(size_t));
        red += sizeof(size_t);
        while (red < limit) {
            Pizza::PizzaType type;
            Pizza::PizzaSize size;
            Pizza::PizzaState state;

            memcpy(&type, (char*)header.buffer + red, sizeof(int));
            red += sizeof(int);
            memcpy(&size, (char*)header.buffer + red, sizeof(int));
            red += sizeof(int);
            memcpy(&state, (char*)header.buffer + red, sizeof(int));
            red += sizeof(int);

            pizzas.push_back(PizzaFactory::createPizza(type, size));
            pizzas.back().setState(state);
        }

    }
    return pizzas;
}

void SfmlIpc::serializePizza(const Pizza & pizza, header_t & header)
{
    header.size = sizeof(int) * 2;
    header.buffer = malloc(sizeof(int) * 2);
    int type = pizza.getPizzaType();
    int size = pizza.getPizzaSize();
    memcpy((char*)header.buffer, &type, sizeof(int));
    memcpy((char*)header.buffer + sizeof(int), &size, sizeof(int));
}

Pizza SfmlIpc::deserializePizza(header_t & header)
{
    Pizza::PizzaType type;
    Pizza::PizzaSize size;
    memcpy(&type, header.buffer, sizeof(int));
    memcpy(&size, (char*)header.buffer + sizeof(int), sizeof(int));
    Pizza p = PizzaFactory::createPizza(type, size);
    return p;
}