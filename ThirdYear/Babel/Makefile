INSTALL_SCRIPT  =   ./unix_setup.sh
BUILD_SCRIPT    =   ./unix_build.sh

NAME_CLIENT =   ./babel_client
NAME_SERVER =   ./babel_server

RM		=			rm -rf

ifeq ($(OS),Windows_NT)
				INSTALL_SCRIPT = windows_setup.bat
				BUILD_SCRIPT   = windows_build.bat

				NAME_CLIENT = babel_client.exe
				NAME_SERVER = babel_server.exe
				RM										=	powershell Remove-Item -Recurse
endif

all: install bin

install:
				$(INSTALL_SCRIPT)

bin:
				$(BUILD_SCRIPT)

clean:
				-$(RM) $(NAME_CLIENT)
				-$(RM) $(NAME_SERVER)

fclean: clean
				-$(RM) build

docs:
				@doxygen Doxyfile

re: fclean all