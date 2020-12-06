/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** NCurses
*/

#include "NCurses.hpp"

typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;

WINDOW *NCurses::create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

NCurses::NCurses(Htop& h)
: _htop (h)
{
    createWindow();
}

void NCurses::printMemory()
{
	std::vector<std::string> parse = {"Total: ", "Free: ", "Available: "}; 
	this->_htop.getRam().parsing();
	int j = -3;
	std::vector<int> t = this->_htop.getRam().getMemoryInfo();

	for (auto i : t) {
		mvprintw(LINES / 2 + j - 1, (COLS / 3), (char*)(parse[j + 3]).c_str());
		mvprintw((LINES / 2) - (t.size() / 2) + j, (COLS / 2) - (std::to_string(i).size() / 2), (char*)(std::to_string(i).c_str()));
		++j;
	}
}

void NCurses::printNetwork()
{
	std::vector<NetworkModule::Network> lNetwork = _htop.getNetwork().getNetworkList();
	int j = -1 * (lNetwork.size() * 5);

	for (auto e : lNetwork) {
		mvprintw((LINES / 2) + ((lNetwork.size() * 5) / 2) + j++, (COLS / 2) - ((std::string("Name: " + e.getName())).size() / 2), (char*)(std::string("Name: " + e.getName())).c_str());
		mvprintw((LINES / 2) + ((lNetwork.size() * 5) / 2) + j++, (COLS / 2) - ((std::string("Received Bit: " + std::to_string(e.getReceivedBytes()))).size() / 2), (char*)((std::string("Received Bit: " + std::to_string(e.getReceivedBytes()))).c_str()));
		mvprintw((LINES / 2) + ((lNetwork.size() * 5) / 2) + j++, (COLS / 2) - ((std::string("Received Packets: " + std::to_string(e.getReceivedPackets()))).size() / 2), (char*)((std::string("Received Packed: " + std::to_string(e.getReceivedPackets()))).c_str()));
		mvprintw((LINES / 2) + ((lNetwork.size() * 5) / 2) + j++, (COLS / 2) - ((std::string("Transmit Bytes: " + std::to_string(e.getTransmitBytes()))).size() / 2), (char*)((std::string("Transmit Bytes: " + std::to_string(e.getTransmitBytes()))).c_str()));
		mvprintw((LINES / 2) + ((lNetwork.size() * 5) / 2) + j++, (COLS / 2) - ((std::string("Transmit Packets: " + std::to_string(e.getTransmitPackets()))).size() / 2), (char*)((std::string("Transmit Packets: " + std::to_string(e.getTransmitPackets()))).c_str()));
	}
}

void NCurses::printSwap()
{
	int j = -2;
	std::vector<std::string> parse = {"Total: ", "Free: "};

	SwapModule t = this->_htop.getSwap();
	for (auto i: t.getSwapVector()) {
		mvprintw(LINES / 2 + j, COLS / 3, (char *)parse[j+2].c_str());
		mvprintw((LINES / 2) + (t.getSwapVector().size() / 2) + j - 1, (COLS / 2) - (std::to_string(i).size() / 2), (char*)(std::to_string(i).c_str()));
		++j;
	}
}

void NCurses::printUser()
{
	UserModule t = this->_htop.getUser();
	mvprintw((LINES / 2) - 1, (COLS / 2) - ((std::string("Hostname: " + t.getHostname())).size() / 2), ((std::string("Hostname: " + t.getHostname()))).c_str());
	mvprintw((LINES / 2), (COLS / 2) - ((std::string("User: " + t.getUsername())).size() / 2), ((std::string("User: " + t.getUsername()))).c_str());
}

void NCurses::printTime()
{
	TimeModule t = this->_htop.getTime();
	mvprintw((LINES / 2) -1, (COLS / 2) - ((std::string("Date: " + t.getDate())).size() / 2), ((std::string("Date: " + t.getDate())).c_str()));
	mvprintw((LINES / 2), (COLS / 2) - ((std::string("Hours: " + t.getHour())).size() / 2), ((std::string("Hours: " + t.getHour())).c_str()));
}

void NCurses::printKernel()
{
	int j = -1;

	KernelModule t = this->_htop.getKernel();

	for (auto i : t.getVectorKernel()) {
		mvprintw((LINES / 2) - (this->_htop.getKernel().getVectorKernel().size() / 2) + j, (COLS / 2) - (i.size() / 2), i.c_str());
		++j;
	}
}

void NCurses::printCPU()
{
	std::vector<Core> core = this->_htop.getCpu().getCores();
	int j = (-1 * (this->_htop.getCpu().getCoreNumber() * 2) + 1);

	for (auto i : core) {
		mvprintw(LINES / 2 - (core.size() / 2) + j, COLS / 3, (char*)(std::string("Percentage: ").c_str()));
		mvprintw((LINES / 2) - (core.size() / 2) + j++, (COLS / 2) - (std::to_string(i.getPercentage()).size() / 2), (char*)(std::to_string(i.getPercentage()).c_str()));
		mvprintw(LINES / 2 - (core.size() / 2) + j, COLS / 3, (char*)(std::string("Max: ").c_str()));
		mvprintw((LINES / 2) - (core.size() / 2) + j++, (COLS / 2) - (std::to_string(i.getMax()).size() / 2), (char*)(std::to_string(i.getMax()).c_str()));
		mvprintw(LINES / 2 - (core.size() / 2) + j, COLS / 3, (char*)(std::string("Usage: ").c_str()));
		mvprintw((LINES / 2) - (core.size() / 2) + j++, (COLS / 2) - (std::to_string(i.getUsage()).size() / 2), (char*)(std::to_string(i.getUsage()).c_str()));
		mvprintw(LINES / 2 - (core.size() / 2) + j, COLS / 3, (char*)(std::string("Min: ").c_str()));
		mvprintw((LINES / 2) - (core.size() / 2) + j++, (COLS / 2) - (std::to_string(i.getMin()).size() / 2), (char*)(std::to_string(i.getMin()).c_str()));
	}
}

void NCurses::printProcess()
{
	int randValue = rand() % this->_htop.getProcess().getList().size();
	std::vector<ProcessModule::Process> t = this->_htop.getProcess().getList();
	int j = -7;
	auto i = t.begin() + randValue;;

	for (int k = 0; k != 1; ++k) {
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("PID: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - (*i).getPid().size(), (char*)(*i).getPid().c_str());
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("User: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - (*i).getUser().size(), (char*)(*i).getUser().c_str());
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("State: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - (*i).getState().size(), (char*)(*i).getState().c_str());
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Virtual: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getVirtual()).size(), (char *)(std::to_string((*i).getVirtual()).c_str()));
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Priority: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getPriority()).size(), (char *)(std::to_string((*i).getPriority()).c_str()));
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Nice: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getNice()).size(), (char *)(std::to_string((*i).getNice()).c_str()));
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Time: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getTime()).size(), (char *)(std::to_string((*i).getTime()).c_str()));
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Uptime: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getUpTime()).size(), (char *)(std::to_string((*i).getUpTime()).c_str()));
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Stime:: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getSTime()).size(), (char *)(std::to_string((*i).getSTime()).c_str()));
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Utime: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getUTime()).size(), (char *)(std::to_string((*i).getUTime()).c_str()));
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("CSTtime: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getCSTime()).size(), (char *)(std::to_string((*i).getCSTime())).c_str());
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("CUTtime: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getCUTime()).size(), (char *)(std::to_string((*i).getCUTime())).c_str());
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("MemTotal: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getMemTotal()).size(), (char *)(std::to_string((*i).getMemTotal())).c_str());
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Res: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getRes()).size(), (char *)(std::to_string((*i).getRes())).c_str());
		mvprintw(LINES / 2 + j, COLS / 3, (char*)(std::string("Shr: ").c_str()));
		mvprintw(LINES / 2 + j++, COLS / 2 - std::to_string((*i).getShr()).size(), (char *)(std::to_string((*i).getShr())).c_str());
	}
}

void NCurses::moduleNotLoaded(const std::string & name)
{
	mvprintw(LINES / 2, COLS / 2 - ((std::string("Module not loaded ") + name).size() / 2), (char*)(((std::string("Module not loaded ") + name).c_str())));
}

void NCurses::drawPage(int page)
{
	this->_htop.refresh(page);

	switch (page) {
		case 0:
			if (this->_htop.getModuleCharge()[Htop::CPU] == true)
				printCPU();
			else
				this->moduleNotLoaded("CPU");
			break;
		case 1:
			if (this->_htop.getModuleCharge()[Htop::MEMORY] == true)
				printMemory();
			else
				this->moduleNotLoaded("MEMORY");
			break;
		case 2:
			if (this->_htop.getModuleCharge()[Htop::NETWORK] == true)
				printNetwork();
			else
				this->moduleNotLoaded("NETWORK");
			break;
		case 3:
			if (this->_htop.getModuleCharge()[Htop::PROCESS] == true)
				printProcess();
			else
				this->moduleNotLoaded("PROCESS");
			break;
		case 4:
			if (this->_htop.getModuleCharge()[Htop::SWAP] == true)
				printSwap();
			else
				this->moduleNotLoaded("SWAP");
			break;
		case 5:
			if (this->_htop.getModuleCharge()[Htop::USER] == true)
				printUser();
			else
				this->moduleNotLoaded("USER");
			break;
		case 6:
			if (this->_htop.getModuleCharge()[Htop::TIME] == true)
				printTime();
			else
				this->moduleNotLoaded("TIME");
			break;
		case 7:
			if (this->_htop.getModuleCharge()[Htop::KERNEL] == true)
				printKernel();
			else
				this->moduleNotLoaded("KERNEL");
			break;
		default:
			break;
	}
}

void NCurses::createWindow()
{
    int ch = -1;

    initscr();
	curs_set(false);
	start_color();

    while(open) {
		clear();
		switch(ch)
		{
			case 'q':
				open = false;
				break;
			case 'Q':
				open = false;
				break;
			case 68:
				--page;
				break;
			case 67:
				++page;
				break;
			default :
				break;
		}
		if (open) {
        	(page > 7) ? (page = 0) : (0);
        	(page < 0) ? (page = 7) : (0);
        	drawPage(page);
		}
		refresh();
		if (open) {
			timeout(1000);
			ch = getch();
		}
	}
	endwin();
}
