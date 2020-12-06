##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC 	=   strlen.asm \
			strchr.asm \
			memset.asm \
			memcpy.asm \
			memmove.asm \
			strcmp.asm \
			strncmp.asm \
			rindex.asm \
			strcasecmp.asm \
			strstr.asm \
			strpbrk.asm \
			strcspn.asm

SRCBONUS =	bonus/index.asm \
			bonus/strncasecmp.asm \
			bonus/strrchr.asm \
			bonus/strspn.asm \
			bonus/strcasestr.asm \

OBJ		=	$(SRC:.asm=.o)

OBJBONUS =	$(SRCBONUS:.asm=.o)

NAME	=	libasm.so

AS		= 	nasm

ASFLAGS	=	-f elf64

CC      =	ld

CFLAGS    =	-fPIC -shared

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(OBJ) $(OBJBONUS)
	$(CC) $(CFLAGS) $(OBJ) $(OBJBONUS) -o $(NAME)

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJ) test
	rm -f *.o

fclean: clean
	rm -f $(NAME) vgcore.*

test: $(NAME)
	gcc main.c -L./ -lasm -fno-builtin -o test
	clear
	LD_LIBRARY_PATH=$(PWD) LD_PRELOAD=$(NAME) ./test

bonustest: bonus
	gcc main.c -L./ -lasm -fno-builtin -o test
	clear
	LD_LIBRARY_PATH=$(PWD) LD_PRELOAD=$(NAME) ./test

re: fclean all

.PHONY: clean re fclean all
