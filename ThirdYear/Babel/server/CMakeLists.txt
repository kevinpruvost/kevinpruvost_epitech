# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (babel_server
"main.cpp"
"networktools/BabelServer.cpp"
"networktools/BabelServer.hpp"
"networktools/BabelClient.cpp"
"networktools/BabelClient.hpp"
"networktools/ClientManager.cpp"
"networktools/ClientManager.hpp"
"database/sqliteDataBase.cpp"
"database/sqliteDataBase.hpp")

target_include_directories(babel_server PUBLIC
	../lib/
)

target_link_libraries(babel_server
	CONAN_PKG::boost
	CONAN_PKG::qt
	CONAN_PKG::portaudio
	CONAN_PKG::opus
)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
