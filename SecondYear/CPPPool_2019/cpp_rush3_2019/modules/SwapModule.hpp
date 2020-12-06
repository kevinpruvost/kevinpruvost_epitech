/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** SwapModule
*/

#ifndef SWAPMODULE_HPP_
#define SWAPMODULE_HPP_

#include "IMonitorModule.hpp"

class SwapModule: public IMonitorModule {
	public:
        enum swap_enum {
            TOTAL,
            FREE
        };
		SwapModule();
		~SwapModule();
        bool parsing() override;
        std::vector<int> getSwapVector() const;
	protected:
	private:
        std::vector<int> swap;
};

#endif /* !SWAPMODULE_HPP_ */
