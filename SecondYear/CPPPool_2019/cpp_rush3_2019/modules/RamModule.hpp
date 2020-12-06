/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** RamModule
*/

#ifndef RAMMODULE_HPP_
#define RAMMODULE_HPP_

#include "IMonitorModule.hpp"

class RamModule : public IMonitorModule {
	public:
		RamModule();
		~RamModule();
		enum ram_swap {
			TOTAL,
			FREE,
			AVAILABLE
		};
        bool parsing() override;
		void setDebug(bool value);
		void displayMemoryInfo();
		void checkInformation();
		std::vector<int> getMemoryInfo();
	private: 
		std::string _path = "/proc/meminfo";
		std::vector<std::string> _lookingFor = {"MemTotal", "MemFree", "MemAvailable"};
		std::vector<int> _memoryinfo;
		bool _debug = false;
};

#endif /* !RAMMODULE_HPP_ */
