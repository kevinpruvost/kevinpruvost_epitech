/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** TimeModule
*/

#ifndef TIMEMODULE_HPP_
#define TIMEMODULE_HPP_

#include "IMonitorModule.hpp"

class TimeModule : public IMonitorModule {
	public:
		TimeModule();
		~TimeModule();
        bool parsing() override;
		std::string getDate() const;
		std::string getHour() const;
	protected:
	private:
        std::string _date;
        std::string _hour;
        bool _debug = false;
};

#endif /* !TIMEMODULE_HPP_ */
