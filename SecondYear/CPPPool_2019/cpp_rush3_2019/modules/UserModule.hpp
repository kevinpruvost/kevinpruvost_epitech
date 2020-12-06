/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** UserModule
*/

#ifndef USERMODULE_HPP_
#define USERMODULE_HPP_

#include <cstdlib>
#include "IMonitorModule.hpp"

class UserModule: public IMonitorModule {
	public:
		UserModule();
		~UserModule();
        bool parsing() override;
        std::string getHostname() const {return (_hostname);}
        std::string getUsername() const {return (_username);}
	protected:
        std::string _hostname;
        std::string _username;
	private:
};

#endif /* !USERMODULE_HPP_ */
