/*
** A Kevin Pruvost's project, May 2020
** SfmlIpc.hpp
** File description:
** sfml ipc
*/

#pragma once

// Project includes
#include "Plazza.hpp"
#include "Ipc.hpp"

// C++ includes
#include <memory>

class SfmlIpc : virtual public Ipc
{
public:
    SfmlIpc();
    ~SfmlIpc();

    header_t getDataFromSentCommand();
    header_t getPizzas() override;
    header_t getKitchens() override;
    header_t addPizza(const Pizza & pizza) override;
    void exit() override;

    void setPlazza(std::shared_ptr<Plazza> & plazza) { _plazza = plazza; }

public:
    void serializeKitchenVector(const std::vector<std::shared_ptr<Kitchen>> & kitchens, header_t & header);
    std::vector<std::unique_ptr<Kitchen>> deserializeKitchenVector(header_t & header);
    void serializePizzaVector(const std::vector<std::shared_ptr<Pizza>> & pizzas, header_t & header);
    std::vector<Pizza> deserializePizzaVector(header_t & header);
    void serializePizza(const Pizza & pizza, header_t & header);
    Pizza deserializePizza(header_t & header);

private:
    std::unique_ptr<std::thread> _read;
    std::shared_ptr<Plazza> _plazza;

    bool gotData = false;
    std::condition_variable condGotData;
    header_t * headerData = nullptr;
};