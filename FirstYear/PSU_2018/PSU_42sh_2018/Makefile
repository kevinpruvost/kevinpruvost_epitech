##
## EPITECH PROJECT, 2018
## 42sh
## File description:
## The program build instructions.
##

CC = gcc
CFLAGS = -O2 -pipe
CFLAGS += -Wall -Wextra -Wshadow -Wuninitialized -Wno-unused-parameter
CFLAGS += -Winit-self -Wpointer-compare -Wundef
CFLAGS += -Iinclude -Ilib/liblist/include
LDFLAGS = -Llib/liblist
LDLIBS = -llist

NAME = 42sh

SRCS = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)
OBJS = $(SRCS:.c=.o)

all :$(NAME)

lib/liblist/liblist.a:
	$(MAKE) -C lib/liblist

$(NAME): lib/liblist/liblist.a
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

clean:
	$(MAKE) -C lib/liblist $@
	$(RM) src/*.o src/**/*.o src/**/**/*.o
	$(RM) src/*.gc* src/**/*.gc* src/**/**/*.gc*

fclean: clean
	$(MAKE) -C lib/liblist $@
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
