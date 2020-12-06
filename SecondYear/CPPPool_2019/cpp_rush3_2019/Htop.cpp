/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** Htop= default
*/

#include "Htop.hpp"

Htop::Htop()
{
}

Htop::~Htop()
{
}

CPUModule Htop::getCpu() const
{
    return this->_cpu;
}

RamModule Htop::getRam() const
{
    return this->_ram;
}

NetworkModule Htop::getNetwork() const
{
    return this->_network;
}

ProcessModule Htop::getProcess() const
{
    return this->_process;
}

SwapModule Htop::getSwap() const
{
    return this->_swap;
}

UserModule Htop::getUser() const
{
    return this->_user;
}

TimeModule Htop::getTime() const
{
    return this->_time;
}

KernelModule Htop::getKernel() const
{
    return this->_kernel;
}

std::vector<bool> Htop::getModuleCharge() const
{
    return this->_moduleCharge;
}

void Htop::refresh(int index = 0)
{
    if (index == 0)
        this->_cpu.parsing();
    else if (index == 1)
        this->_ram.parsing();
    else if (index == 2)
        this->_network.parsing();
    else if (index == 3)
        this->_process.parsing();
    else if (index == 4)
        this->_swap.parsing();
    else if (index == 5)
        this->_user.parsing();
    else if (index == 6)
        this->_time.parsing();
    else if (index == 7)
        this->_kernel.parsing();
}

void Htop::my_strcat()
{
    std::ifstream inFile(this->_filename);
    std::string buffer;

    if (inFile.is_open()) {
        while (std::getline (inFile, buffer))
            std::cout << buffer << std::endl;
    } else if (this->_debug == true) {
        std::cerr << "my_cat: " << this->_filename
            << ": No such file or directory" << std::endl;
    }
    inFile.close();
}

void Htop::displayArgParssing() const
{
    auto i = this->_parssInfo.begin();
    for (auto j: this->_moduleCharge) {
        std::cout << *i << ": " << j << std::endl;
        ++i;
    }
}

int Htop::parssing(int ac, char **av)
{
    bool cpu = true;
    bool memory = true;
    bool network = true;
    bool process = true;
    bool swap = true;
    bool text = true;
    bool graphics = false;
    bool user = true;
    bool kernel = true;
    bool time = true;

    for (int i = 1; i < ac; ++i) {
        if (this->_debug == true)
            std::cerr << "Read : " << av[i] << std::endl;
        std::string str = av[i];
        if (strcmp(av[i], "-c") == 0)
            cpu = false;
        else if (strcmp(av[i], "-m") == 0)
            memory = false;
        else if (strcmp(av[i], "-n" ) == 0)
                network = false;
        else if (strcmp(av[i], "-p") == 0)
            process = false;
        else if (strcmp(av[i], "-s") == 0)
            swap = false;
        else if (strcmp(av[i], "--graphics") == 0){
            text = false;
            graphics = true;
        } else if (strcmp(av[i], "--text") == 0)
            text = true;
        else if (strcmp(av[i], "-h") == 0) {
            Htop::my_strcat();
            return EXIT_FAILURE;
        } else if (strcmp(av[i], "--help") == 0) {
            Htop::my_strcat();
            return EXIT_FAILURE;
        } else if (strcmp(av[i], "-u") == 0) {
            user = false;
        } else if (strcmp(av[i], "-t") == 0) {
            time = false;
        } else if (strcmp(av[i], "-k") == 0) {
            kernel = false;
        } else {
            std::cerr << "wrong arguments" << std::endl;
            return EXIT_FAILURE;
        }
    }
    if (!cpu && !memory && !network && !process && !swap) {
        std::cerr << "All module is disable" << std::endl;
        return EXIT_FAILURE;
    }
    this->_moduleCharge.push_back(cpu);
    this->_moduleCharge.push_back(memory);
    this->_moduleCharge.push_back(network);
    this->_moduleCharge.push_back(process);
    this->_moduleCharge.push_back(swap);
    this->_moduleCharge.push_back(graphics);
    this->_moduleCharge.push_back(text);
    this->_moduleCharge.push_back(user);
    this->_moduleCharge.push_back(kernel);
    this->_moduleCharge.push_back(time);
    if (this->_debug == true)
        displayArgParssing();
    return EXIT_SUCCESS;
}

void Htop::chargeModule()
{
    int index = 0;

    for (auto i : this->_moduleCharge) {
        if (i == true) {
            if (index == 0)
                this->_cpu.parsing();
            else if (index == 1)
                this->_ram.parsing();
            else if (index == 2)
                this->_network.parsing();
            else if (index == 3)
                this->_process.parsing();
            else if (index == 4)
                this->_swap.parsing();
            else if (index == 7)
                this->_user.parsing();
            else if (index == 8)
                this->_time.parsing();
            else if (index == 9)
                this->_kernel.parsing();
        }
        index++;
    }
}

bool Htop::getBool(Htop::enum_module index) const
{
    return _moduleCharge[index];
}
