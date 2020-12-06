/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** Htop
*/

#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <memory>

#include "modules/CPUModule.hpp"
#include "modules/NetworkModule.hpp"
#include "modules/ProcessModule.hpp"
#include "modules/RamModule.hpp"
#include "modules/SwapModule.hpp"
#include "modules/TimeModule.hpp"
#include "modules/KernelModule.hpp"
#include "modules/UserModule.hpp"

class Htop
{
	public:
		Htop();
		~Htop();
		enum enum_module {
			CPU,
			MEMORY,
			NETWORK,
			PROCESS,
			SWAP,
			GRAPHICS,
			TEXT,
			USER,
			KERNEL,
			TIME
		};
		void my_strcat();
		int parssing(int ac, char **av);
		void displayArgParssing() const;
		void chargeModule();
		bool getBool(enum_module index) const;
		void refresh(int index);
		CPUModule getCpu() const;
		RamModule getRam() const;
		NetworkModule getNetwork() const;
		ProcessModule getProcess() const;
		SwapModule getSwap() const;
		UserModule getUser() const;
		TimeModule getTime() const;
		KernelModule getKernel() const;
		std::vector<bool> getModuleCharge() const;
	protected:
		std::string _filename = "./README.md";
		bool _debug = false;
		std::vector<bool> _moduleCharge;
		std::vector<std::string> _parssInfo = {"Cpu", "Memory", "Network",
			"Process", "Swap", "Graphics", "Text", "User", "Time", "Kernel"};
		CPUModule _cpu;
		RamModule _ram;
		NetworkModule _network;
		ProcessModule _process;
		SwapModule _swap;
		UserModule _user;
		TimeModule _time;
		KernelModule _kernel;
};
