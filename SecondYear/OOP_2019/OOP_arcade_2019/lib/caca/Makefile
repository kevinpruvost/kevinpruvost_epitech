##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC		= 	Caca.cpp \
			../../include/ArcadeEvent.cpp \
			../../include/ArcadeContent.cpp \
			../../include/SpriteData.cpp \
			../../include/ADisplayModule.cpp \
			../../include/AModule.cpp \
			../../include/Exception.cpp \

OBJ		=	$(SRC:.cpp=.o)

NAME	=	../lib_arcade_caca.so

CXX         =	g++
CXXFLAGS    = 	-I./ -I../../include -I./import/include -I./import/
CXXFLAGS	+= 	-L./import/
CXXFLAGS	+= 	-lcaca
CXXFLAGS	+= 	-fPIC -pipe -g -Wall

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)

%.o:	%.cpp
	$(CXX) $< -c -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(OBJTEST)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
