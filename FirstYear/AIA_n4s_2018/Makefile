##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

NAME	=	ai

SRC	=	$(wildcard *.c)				\
		$(wildcard get_info/*.c)		\
		bonus/help_option.c			\
\
		$(wildcard lib/*.c)			\

OBJ	=	$(SRC:.c=.o)

SRC_B	=	ai.c					\
		calcul_angle.c				\
		create_ai.c				\
		detect_collision.c			\
		detect_end.c				\
		launch_command.c			\
		redirected.c				\
		redirected_calculate.c			\
		wheels_dir.c				\
		$(wildcard bonus/*.c)			\
		$(wildcard get_info/*.c)		\
\
		$(wildcard lib/*.c)			\
		$(wildcard lib/csfml/*.c)		\
		$(wildcard lib/csfml/time/*.c)		\
		$(wildcard lib/csfml/obj_mod/*.c)	\
		$(wildcard lib/csfml/sprite_mod/*.c)	\
		$(wildcard lib/csfml/animation/*.c)	\

OBJ_B	=	$(SRC_B:.c=.o)

CC	=	@gcc

CFLAGS	=	-g -O2 -I./include -lm

CSFML	=	-lcsfml-window -lcsfml-graphics -lcsfml-system -lcsfml-audio

all:	compil run compile

compil:
	@echo "Compilation..."

compile:
	@echo "Compilation completed."

run:	$(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@rm -f $(OBJ) $(OBJ_B)

fclean:	clean
	@rm -f $(NAME)

test:
	@make
	./pipes.sh

re:	fclean all

bonus:	$(OBJ_B)
	@gcc -o $(NAME) $(OBJ_B) $(CFLAGS) $(CSFML)

.PHONY:	all clean fclean re
