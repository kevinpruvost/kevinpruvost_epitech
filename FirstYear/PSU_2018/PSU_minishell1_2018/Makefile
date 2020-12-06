##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

SRC	=	main.c			\
		my_exec.c		\
		my_exec2.c		\
		special_programs.c	\
		special_programs2.c	\
		path.c			\
		path2.c			\
		shortkeys.c		\
		setenv.c		\
		search_env.c		\
		free.c			\
		signals.c		\
		cd.c			\
\
		lib/my_atoi.c		\
		lib/my_putstr.c		\
		lib/my_strlen.c		\
		lib/my_getfloat.c	\
		lib/my_getnbr.c		\
		lib/my_revstr.c		\
		lib/str_add.c		\
		lib/my_put_nbr.c	\
		lib/my_putchar.c	\
		lib/my_strcpy.c		\
		lib/str_add_to_array.c	\
		lib/my_arraylen.c	\
		lib/is_str.c		\
		lib/str_to_word_array.c	\
		lib/my_putstr_error.c	\
		lib/is_file.c		\
		lib/get_next_line.c	\

SRC_B	=	bonus/main.c		\
		bonus/main2.c		\
		my_exec.c               \
                my_exec2.c              \
                special_programs.c      \
		special_programs2.c	\
                path.c                  \
                path2.c                 \
                shortkeys.c             \
                setenv.c                \
                search_env.c            \
                free.c                  \
		signals.c		\
		cd.c			\
\
                lib/my_atoi.c           \
                lib/my_putstr.c         \
                lib/my_strlen.c         \
                lib/my_getfloat.c       \
                lib/my_getnbr.c         \
                lib/my_revstr.c         \
                lib/str_add.c           \
                lib/my_put_nbr.c        \
                lib/my_putchar.c        \
                lib/my_strcpy.c         \
                lib/str_add_to_array.c  \
                lib/my_arraylen.c       \
                lib/is_str.c            \
                lib/str_to_word_array.c \
                lib/my_putstr_error.c   \
		lib/is_file.c		\
		lib/get_next_line.c	\


NAME    =       mysh

all:
	gcc $(SRC) -o $(NAME) -I./include -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

bonus:	fclean
	gcc $(SRC_B) -o $(NAME) -I./include -g

.PHONY: all clean fclean
