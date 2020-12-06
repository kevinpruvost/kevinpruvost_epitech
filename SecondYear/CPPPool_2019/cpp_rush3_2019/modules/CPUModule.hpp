/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** CPUModule
*/

#pragma once

#include "IMonitorModule.hpp"

class Core
{
	public:
		Core() { }
		~Core() { }

	public:
		double getPercentage() const { return _percentage; }
		double getMax() const { return _max; }
		double getUsage() const { return _usage; }
        double getMin() const { return _min; }

		void setPercentage(double percentage) { _percentage = percentage; }
		void setMax(double percentage) { _max = percentage; }
		void setUsage(double percentage) { _usage = percentage; }
        void setMin(double percentage) { _min = percentage; }

    public:
		double _percentage = 0;
        double _min = 0;
		double _max = 0;
		double _usage = 0;
};

class CPUModule: public IMonitorModule
{
	public:
		CPUModule();
		~CPUModule();
        bool parsing() override;

		int getCoreNumber() const { return _coreNumber; }
        const std::vector<Core> &getCores() const { return _cores; }
        Core & getActualCore() { return _cores.back(); }

	private:
		int _coreNumber = 0;
        std::vector<Core> _cores;
		int _uptime = 0;
};
