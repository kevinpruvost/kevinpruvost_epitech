/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IMonitorDisplay.hpp"
#include "../Htop.hpp"
#include <curses.h>

class NCurses : public IMonitorDisplay {
	public:
		NCurses(Htop& h);
		~NCurses() {};
		void createWindow() override;
		WINDOW *create_newwin(int height, int width, int starty, int startx);
		void printSomething();
		void printKernel();
		void printTime();
		void printUser();
		void printSwap();
		void printProcess();
		void printNetwork();
		void printMemory();
		void printCPU();
		void drawPage(int page);
		void moduleNotLoaded(const std::string &name);
	protected:
	private:
		bool open = true;
		int save = -1;
		int page = 8;
		Htop _htop;
};

#endif /* !NCURSES_HPP_ */
