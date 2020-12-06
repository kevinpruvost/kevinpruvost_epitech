##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC		= 	src/main.cpp \
			src/MainWindow.cpp \
			src/DLLoader.cpp \
			src/ArcadeDLLoader.cpp \
			include/ReadDir.cpp \
			include/ArcadeEvent.cpp \
			include/ArcadeContent.cpp \
			include/Exception.cpp \

OBJ		=	$(SRC:.cpp=.o)

NAME	=	arcade

CXX         =	g++
CXXFLAGS    =	-I./src -I./include -fpermissive -fPIC -pipe -g -Wall -ldl

all: $(NAME)

compilegames:
	@make --no-print-directory -C games/

games: compilegames

graphicals:
	@make --no-print-directory -C lib/

$(NAME): games graphicals core

core:	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	@make --no-print-directory clean -C lib/ 
	@make --no-print-directory clean -C games/
	@make --no-print-directory clean -C bonus/tests/
	rm -f $(OBJ)
	rm -f *.so

fclean:
	@make --no-print-directory fclean -C lib/
	@make --no-print-directory fclean -C games/
	@make --no-print-directory fclean -C bonus/tests/
	rm -f $(NAME) vgcore.*
	rm -f $(OBJ)
	rm -f *.so

test: $(NAME)
	@make --no-print-directory -C bonus/tests/
	@./bonus/tests/test
	@make --no-print-directory clean -C bonus/tests/

re: fclean all

.PHONY: clean re fclean all