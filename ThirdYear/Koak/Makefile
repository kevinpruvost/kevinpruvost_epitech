##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## makefile
##

STACK	=	stack

NAME	=	koak
NAME2	=	koakc
PATHEXE	=	$(shell $(STACK) path --local-install-root)/bin/
EXT		=	
CP		=	cp -f
ADD		=	#&& mv -f .$(NAME) $(NAME)

ifeq ($(OS),Windows_NT)
	PATHEXE=$(shell $(STACK) path --local-install-root)\bin\
	EXT=.exe
	ADD=
	CP=copy
endif

all:
	$(STACK) build
	$(CP) $(PATHEXE)$(NAME)$(EXT) . $(ADD)
	$(CP) $(PATHEXE)$(NAME2)$(EXT) . $(ADD)

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