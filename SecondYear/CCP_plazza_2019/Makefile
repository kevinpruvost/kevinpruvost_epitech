##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## clean rule
##

SRCMAIN	=   main.cpp \

SRCFILE	=	Plazza.cpp \
			Kitchen/Kitchen.cpp \
			Exception.cpp \
			CondVar.cpp \
			Shell.cpp \
			Thread.cpp \
			Manager.cpp \
			Process.cpp \
			Ipc.cpp \
			Ingredients/Ingredient.cpp \
			Ingredients/Stock.cpp \
			Kitchen/Cook.cpp \
			Kitchen/KitchenFactory.cpp \
			Kitchen/KitchenProcess.cpp \
			Pizzas/Pizza.cpp \
			Pizzas/Americana.cpp \
			Pizzas/Regina.cpp \
			Pizzas/Fantasia.cpp \
			Pizzas/Margarita.cpp \
			Pizzas/PizzaFactory.cpp \
			Pizzas/pizza_utils.cpp \

BONFILE	=	MainWindow.cpp \
			Menu.cpp \
			Game.cpp \
			Page.cpp \
			SfmlIpc.cpp \
			SfmlPlazza.cpp \

SRC		=	$(SRCMAIN) \
			$(addprefix src/, $(SRCFILE)) \

SRCB1	=	$(addprefix src/, $(SRCFILE)) \

SRCB2	=	$(addprefix bonus, /$(SRCMAIN)) \
			$(addprefix bonus/src/, $(BONFILE)) \

OBJ		=	$(SRC:.cpp=.o)
OBJB1	=	$(SRCB1:.cpp=.o)
OBJB2	=	$(SRCB2:.cpp=.o)
OBJB	=	$(OBJB1) $(OBJB2)

NAME	=	plazza

CXX         =	g++
CXXFLAGS    =	-I./ -I./src/ -I./src/Pizzas/ -I./src/Kitchen/ -I./src/Ingredients/
CXXFLAGS	+=	-fpermissive -pipe -g -Wall -lpthread
CXXFLAGSB	=	$(CXXFLAGS)
CXXFLAGSB	+=	-I./bonus -I./bonus/src/
CXXFLAGSB	+=	-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJB2): %.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGSB)

bonus:	$(OBJB)
	$(CXX) -o $(NAME) $(OBJB) $(CXXFLAGSB)

clean:
	rm -f $(OBJ)
	rm -f $(OBJB)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
