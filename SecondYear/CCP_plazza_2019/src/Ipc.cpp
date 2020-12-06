/*
** A Kevin Pruvost's project, May 2020
** Ipc.cpp
** File description:
** ipc
*/

#include "Ipc.hpp"

Ipc::Ipc()
    : Process()
{
    init();
}

Ipc::~Ipc()
{
}

// Data here is allocated, be aware.
header_t * Ipc::getData()
{
    return readBinary();
}

template<typename T>
void Ipc::sendData(T toSend, Command command)
{
    void * data = static_cast<void *>(toSend);
    header_t header;
    header.command = command;
    header.buffer = data;
    write(header);
}