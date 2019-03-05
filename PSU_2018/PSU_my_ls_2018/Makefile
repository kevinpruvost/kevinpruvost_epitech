##
## EPITECH PROJECT, 2018
## makefile
## File description:
## ah
##

SRC	=	lib/my_atoi.c	\
		lib/my_putstr.c	\
		lib/my_strlen.c	\
		lib/my_getfloat.c	\
		lib/my_getnbr.c		\
		lib/my_revstr.c		\
		lib/str_add.c		\
		lib/my_put_nbr.c	\
		lib/my_putchar.c	\
		lib/my_strcpy.c		\
		lib/str_add_to_array.c	\
		lib/my_revlist.c	\
\
		main.c			\
		main2.c			\
		ntih.c			\
		info_file.c		\
		help_option.c		\
		data.c			\
		data2.c			\
		print_data.c		\
		sort_dir_t.c		\
		sort_dir_t2.c		\
		reverse.c		\
		time.c			\
		utilities.c		\
		options.c		\
		options2.c		\
		manage_arg.c		\
		error_management.c	\

NAME	=	my_ls

all:
	gcc $(SRC) -o $(NAME) -I./include -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
