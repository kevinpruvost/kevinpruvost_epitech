##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC		= 	Sdl.cpp \
			../../include/ArcadeEvent.cpp \
			../../include/ArcadeContent.cpp \
			../../include/SpriteData.cpp \
			../../include/ADisplayModule.cpp \
			../../include/AModule.cpp \
			../../include/Exception.cpp \

OBJ		=	$(SRC:.cpp=.o)

NAME	=	../lib_arcade_sdl.so

CXX         =	g++
CXXFLAGS    =	-I./ -I../../include -I./import/include -fPIC -pipe -g -Wall
CXXFLAGS	+=	-L./import -lSDL2main -lSDL2 -lSDL2_image

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
