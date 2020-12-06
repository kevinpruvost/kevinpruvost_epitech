##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRCBASE =   Circuit.cpp \
			Exception.cpp \
			Parser.cpp \
			AddValue.cpp \
			Shell.cpp \
        	$(wildcard components/*.cpp) \
			bonus/CChar.cpp

SRC		= 	$(SRCBASE) \
			main.cpp

SRCB	=	$(SRCBASE) \
			$(wildcard bonus/graphic/*.cpp)

OBJ		=	$(SRC:.cpp=.o)

OBJB 	=	$(SRCB:.cpp=.o)

NAME	=	nanotekspice

CXX         =	g++
CXXFLAGS    =	-I./ -I./components/ -fpermissive -pipe -g -std=gnu++11 -Wall
CXXFLAGSGR 	=	$(CXXFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

bonheur:	$(OBJB)
	$(CXX) -o $(NAME) $(OBJB) $(CXXFLAGSGR)

clean:
	rm -f $(OBJ)
	rm -f $(OBJB)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
