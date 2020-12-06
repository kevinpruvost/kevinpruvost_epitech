/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** KernelModule
*/

#ifndef KERNELMODULE_HPP_
#define KERNELMODULE_HPP_

#include "IMonitorModule.hpp"

class KernelModule : public IMonitorModule{
	public:
        enum kernel {
            SYSNAME,
            RELEASE,
            VERSION,
            MACHINE
        };
		KernelModule();
		~KernelModule();
        std::vector<std::string> getVectorKernel() const;
        bool parsing() override;
	protected:
	private:
        std::vector<std::string> _kernel;
};

#endif /* !KERNELMODULE_HPP_ */
