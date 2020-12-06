INSTALL_SCRIPT  =   ./unix_setup.sh
BUILD_SCRIPT    =   ./unix_build.sh

NAME_CLIENT =   r-type_client
NAME_SERVER =   r-type_server
NAME_TEST	=	r-type_unit_tests
NAME_BMARK	=	r-type_benchmarks

NAME_LIB	=	common_library
NAME_LIB2	=	testDLLoader

NAME_CLIENTEXE =   r-type_client
NAME_SERVEREXE =   r-type_server
NAME_TESTEXE	=	r-type_unit_tests
NAME_BMARKEXE	=	r-type_benchmarks

RM		=		rm -rf
COPY	=		cp
SEP		=		/
CLEAR	=		clear
OPEN_LINK	=	xdg-open

ifeq ($(OS),Windows_NT)
	INSTALL_SCRIPT =	windows_setup.bat
	BUILD_SCRIPT   =	windows_build.bat

	NAME_CLIENTEXE	=	r-type_client.exe
	NAME_SERVEREXE	=	r-type_server.exe
	NAME_TESTEXE	=	r-type_unit_tests.exe
	NAME_BMARKEXE	=	r-type_benchmarks.exe
	RM			=	powershell Remove-Item -Recurse
	COPY		=	copy
	SEP			=	\\
	CLEAN		=	cls
	OPEN_LINK	=	start
endif

all: install bin

install:
	$(INSTALL_SCRIPT)

bin: bin_server bin_client

bin_server:
	cd build && cmake --build . --target $(NAME_SERVER) && $(COPY) ..$(SEP)build$(SEP)bin$(SEP)$(NAME_SERVEREXE) ..$(SEP)$(NAME_SERVEREXE)

bin_client:
	cd build && cmake --build . --target $(NAME_CLIENT) && $(COPY) ..$(SEP)build$(SEP)bin$(SEP)$(NAME_CLIENTEXE) ..$(SEP)$(NAME_CLIENTEXE)

common_library:
	cd build && cmake --build . --target $(NAME_LIB)

clean:
	-$(RM) $(NAME_CLIENTEXE)
	-$(RM) $(NAME_SERVEREXE)
	-$(RM) $(NAME_TESTEXE)
	-$(RM) $(NAME_BMARKEXE)

fclean: clean
	-$(RM) build

docs:
	@doxygen Doxyfile && $(OPEN_LINK) doc/doxygen/html/index.html

test_install:
	-git submodule update --init benchmarks/googlebenchmarksetup
	$(INSTALL_SCRIPT)

test_lib:
	cd build && cmake --build . --target $(NAME_LIB2)

test: test_lib
	cd build && cmake --build . --target $(NAME_TEST) && $(COPY) ..$(SEP)build$(SEP)bin$(SEP)$(NAME_TESTEXE) ..$(SEP)$(NAME_TESTEXE)
	@./$(NAME_TESTEXE)

test_client: bin_client
	@./$(NAME_CLIENTEXE)

test_server: bin_server
	@./$(NAME_SERVEREXE)

benchmark_install:
	-git submodule update --init benchmarks/googlebenchmarksetup
	$(INSTALL_SCRIPT)

benchmark:
	cd build && cmake --build . --target $(NAME_BMARK) && $(COPY) ..$(SEP)build$(SEP)bin$(SEP)$(NAME_BMARKEXE) ..$(SEP)$(NAME_BMARKEXE)
	@./$(NAME_BMARKEXE)

re: fclean all