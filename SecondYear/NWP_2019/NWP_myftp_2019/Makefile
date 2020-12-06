##
## EPITECH PROJECT, 2020
## Make file
## File description:
## clean rule
##

SRC	=	main.c \
		help.c \
		network.c \
		ftp.c \
		client.c \
		read_sockets.c \
		multi_tok.c \
		tools.c \
		tools2.c \
		sighandlers.c \
		sighandlers2.c \
		ftp/port_pasv.c \
		ftp/list.c \
		ftp/identify.c \
		ftp/noop.c \
		ftp/send.c \
		ftp/pasv.c \
		ftp/port.c \
		ftp/pwd.c \
		ftp/quit.c \
		ftp/retr.c \
		ftp/stor.c \
		ftp/user.c \
		ftp/help.c \
		ftp/dele.c \
		ftp/cwd.c \
		ftp/cdup.c \
		ftp/fork.c \

SRCC	=	bonus/client/main.c \

SRCCBOMB	=	bonus/bomb_client/main.c \

OBJ			=	$(SRC:.c=.o)
OBJC		=	$(SRCC:.c=.o)
OBJCBOMB	=	$(SRCCBOMB:.c=.o)

NAME	=	myftp
NAMEC	=	cl
NAMECBOMB	=	client_bomb

CC		=	gcc
CFLAGS	=	-I./ -I./my_ls/include/ -fPIC -pipe -g -Wall

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(OBJC)
	rm -f *.so
	rm -f vgcore.*

fclean:	clean
	rm -f $(NAME)
	rm -f $(NAMEC)

re:	fclean	all

.PHONY:	clean re fclean all