##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## makefile
##

PIP_INSTALL	=	pip3 install
PY_INSTALLER = pyinstaller
NAME	=	pbrain-gomoku-ai
CP	=	cp -f
RM = rm -f
RM_DIR = rm -rf

SRC = 	./main.py

INSTALL_PROCESS = $(CP) ./main.py ./$(NAME); chmod +x $(NAME)

ifeq ($(OS),Windows_NT)
	CP=copy
	RM=powershell Remove-Item -Recurse
	RM_DIR=powershell Remove-Item -Recurse
	INSTALL_PROCESS = $(PIP_INSTALL) $(PY_INSTALLER) & \
										$(PY_INSTALLER) $(SRC) --name $(NAME) --onefile & \
										$(CP) .\\dist\\$(NAME).exe .\$(NAME).exe
endif

all:
	$(INSTALL_PROCESS)

clean:
	@-$(RM) *.spec
	@-$(RM_DIR) dist
	@-$(RM_DIR) build
	@-$(RM_DIR) __pycache__
	@-$(RM_DIR) src\\__pycache__

fclean: clean
	@-$(RM) $(NAME).exe
	@-$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
