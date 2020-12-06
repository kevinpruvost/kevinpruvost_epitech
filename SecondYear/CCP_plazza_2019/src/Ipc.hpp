/*
** A Kevin Pruvost's project, May 2020
** Ipc.hpp
** File description:
** ipc
*/

#pragma once

// Project includes
#include "Process.hpp"
#include "PizzaFactory.hpp"

class Ipc : virtual public Process
{
public:
    Ipc();
    ~Ipc();

    template<typename T>
    void sendData(T toSend, Command command);
    header_t * getData();

    virtual header_t getPizzas() = 0;
    virtual header_t getKitchens() = 0;
    virtual header_t addPizza(const Pizza & pizza) = 0;
    virtual void exit() = 0;

protected:
private:
    Process process;
};