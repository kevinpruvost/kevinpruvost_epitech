##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## makefile
##

STACK	=	stack

NAME	=	imageCompressor
PATHEXE	=	$(shell $(STACK) path --local-install-root)/bin/$(NAME)

all:
	@$(STACK) build
	@cp -f $(PATHEXE) ./

clean:
	rm -f *.o
	rm -f *.hi
	rm -rf .stack-work

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
