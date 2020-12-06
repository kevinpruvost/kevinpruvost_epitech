##
## EPITECH PROJECT, 2018
## Makefile
## File description:
##
##

SRC	=	my_putstr.c				\
		my_putchar.c				\
		my_compute_square_root.c		\
		my_getnbr.c				\
		my_is_prime.c				\
		my_put_nbr.c				\
		my_putnbr_base.c			\
		my_revstr.c				\
		my_showmem.c				\
		my_showstr.c				\
		my_show_word_array.c			\
		my_sort_int_array.c			\
		my_strcmp.c				\
		my_strcpy.c				\
		my_str_islower.c			\
		my_str_isnum.c				\
		my_str_isprintable.c			\
		my_str_isupper.c			\
		my_strlen.c				\
		my_strlowcase.c				\
		my_strncmp.c				\
		my_strncpy.c				\
		my_strstr.c				\
		my_strupcase.c				\
		my_swap.c				\
		my_atoi.c				\
		addition.c		\
		infin_mult.c		\
		soustraction.c		\
		soustraction2.c		\
		infin_add.c		\
		multiplication.c	\
		multiplication2.c	\
		infin_sub.c		\
		infin_div.c		\
		infin_modulo.c	\
		my_erasestr.c	\
		str_add.c		\
		sum_stdarg.c	\
		disp_stdarg.c	\
		is_alphabet.c	\
		my_putnbrforprintf.c	\
		my_putnbrforprintf2.c	\
		my_put_float.c		\
		str_to_int.c		\
		my_getnbrforprintf.c	\
		my_getnbrforprintf2.c	\
		my_printf/case_bxo.c				\
		my_printf/case_cs.c				\
		my_printf/case_diu.c				\
		my_printf/case_norm.c				\
		my_printf/case_pfs.c				\
		my_printf/flags_my_printf.c				\
		my_printf/identify_str_sorted.c				\
		my_printf/my_printf.c				\
		my_printf/sort_my_printf.c				\
		my_printf/sort_my_printf2.c				\
		my_printf/special_flags.c				\
		

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -c $(SRC)
	ar rc libmy.a $(OBJ)
clean:
	rm -f $(OBJ)
fclean:	clean
	rm -f $(NAME)
	rm -f libmy.a

re:	fclean all

.phony:	re fclean clean all
