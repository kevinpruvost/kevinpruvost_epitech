/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** plazza
*/

// Project includes
#include "MainWindow.hpp"
#include "SfmlPlazza.hpp"

static void signalHandler(int sig)
{
    if (sig == SIGINT)
        workingProcess = false;
}

int main(int argc, const char ** argv)
{
	DEBUG_OFF;

	if (argc != 4)
	{
		if (argc == 5 && (std::string(argv[4]) == "-d" || std::string(argv[4]) == "--debug"))
		{
			DEBUG_ON;
		}
		else
		{
			std::cerr << "Wrong number of arguments." << std::endl;
			std::cerr << "Plazza must be launched like that :\n\n\t"
						 "./plazza COOKING_TIME_MULTIPLIER COOKS_PER_KITCHEN INGREDIENTS_RESPAWN_TIME" << std::endl;
			std::cerr << "\n\tYou can optionnaly add to last parameter \"-d\" or \"--debug\" to print debug log.\n" << std::endl;
			return EXIT_FAILURE;
		}
	}

    signal(SIGINT, signalHandler);

	try {
		std::shared_ptr<MainWindow> mainWindow;
		std::shared_ptr<Plazza> plazza;
		SfmlIpc ipc;

		if (ipc.isChild())
		{
			mainWindow.reset(new MainWindow(ipc));
			return mainWindow->exec();
		}

		plazza.reset(new Plazza(argv));
		ipc.setPlazza(plazza);
		if (isChildProcess)
			return EXIT_SUCCESS;

		return plazza->exec();
	} catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}