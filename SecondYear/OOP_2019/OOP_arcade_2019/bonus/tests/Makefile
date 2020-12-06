##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC		=	../../src/MainWindow.cpp \
			../../src/DLLoader.cpp \
			../../src/ArcadeDLLoader.cpp \
			../../include/ArcadeEvent.cpp \
			../../include/ReadDir.cpp \
			../../include/ArcadeContent.cpp \
			../../include/Exception.cpp \
			main.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	test

CXX         =	g++
CXXFLAGS    =	-I./import -fpermissive -pipe -g -Wall -ldl
CXXFLAGS	+=	-I../../include -I../../src

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(NAME) vgcore.*
	@rm -f $(OBJ)

re: fclean all

.PHONY: clean re fclean all