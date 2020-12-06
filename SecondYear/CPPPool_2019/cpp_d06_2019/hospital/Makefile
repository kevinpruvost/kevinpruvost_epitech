##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC =	SickKoala.cpp \
		KoalaNurse.cpp \
		KoalaDoctor.cpp \
		SickKoalaList.cpp \
		KoalaNurseList.cpp \
		KoalaDoctorList.cpp \
		Hospital.cpp \
		main.cpp

OBJ = $(SRC:.cpp=.o)

NAME =	hospital

CC 		= 	g++

CFLAGS	=	-fno-builtin -std=gnu11 -Wall -Wextra -g

all: $(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean: 
	rm -f $(OBJ) $(OBJTEST)

fclean: clean
	rm -f $(NAME) $(NAMETEST) vgcore.*

re: fclean all