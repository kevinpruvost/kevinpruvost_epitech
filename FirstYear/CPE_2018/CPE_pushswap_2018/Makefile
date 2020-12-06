##
## EPITECH PROJECT, 2018
## makefile
## File description:
## ah
##

SRC	=	operations.c	\
		lib/my_atoi.c	\
		lib/my_putstr.c	\
		lib/my_strlen.c	\
		lib/my_getfloat.c	\
		lib/my_getnbr.c		\
		lib/my_revstr.c		\
		lib/str_add.c		\
		lib/load_file_in_mem.c	\
		lib/my_put_nbr.c	\
		lib/my_putchar.c	\
		main.c			\
		op_trad.c		\
		op_trad2.c		\
		op_trad3.c		\
		selection_sorting.c	\
		insertion_sorting.c	\
		sorted.c

BON	=	operations.c    \
                lib/my_atoi.c   \
                lib/my_putstr.c \
                lib/my_strlen.c \
                lib/my_getfloat.c       \
                lib/my_getnbr.c         \
                lib/my_revstr.c         \
                lib/str_add.c           \
                lib/load_file_in_mem.c  \
                lib/my_put_nbr.c        \
                lib/my_putchar.c        \
                bonus/main.c                  \
		bonus/second_main.c	\
		bonus/selection_sorting_option.c	\
		bonus/op_trad.c               \
                bonus/op_trad2.c              \
                bonus/op_trad3.c              \
                op_trad.c               \
                op_trad2.c              \
                op_trad3.c              \
                selection_sorting.c     \
                insertion_sorting.c     \

NAME	=	push_swap

all:
	gcc $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

bonus:	fclean
	gcc $(BON) -o $(NAME)

.PHONY: all clean fclean
