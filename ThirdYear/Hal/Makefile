##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## makefile
##

STACK	=	stack

NAMEB	=	hal-exe
NAME	=	hal
PATHEXE	=	$(shell $(STACK) path --local-install-root)/bin/$(NAMEB)
CP		=	cp -f
ADD		=	&& mv -f .$(NAME) $(NAME)

ifeq ($(OS),Windows_NT)
	PATHEXE=$(shell $(STACK) path --local-install-root)\bin\$(NAMEB).exe
	NAME=hal.exe
	ADD=
	CP=copy
endif

all:
	$(STACK) build
	$(CP) $(PATHEXE) .\$(NAME) $(ADD)

clean:
	@-rm -f *.o
	@-rm -f *.hi
	@-rm -rf .stack-work

fclean: clean
	@-rm -f $(NAME)

unitTest:
	$(STACK) test

re: fclean all

.PHONY: all clean fclean re