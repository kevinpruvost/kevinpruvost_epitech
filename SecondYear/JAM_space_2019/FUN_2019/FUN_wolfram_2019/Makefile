CC = ghc --make

NAME = wolfram

SRC = 	wolfram.hs \

all:
	ghc --make $(SRC) -o $(NAME)

clean:
	rm $(NAME)

fclean: clean
	rm *.o
	rm *.hi

re: fclean all

.PHONY: all clean fclean re
