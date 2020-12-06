# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_BINARY_DIR}")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (r-type_client
	"main.cpp"
	"Client.hpp"
	"Client.cpp"

	#Network communcation

	"NetworkClient/INetworkClient.hpp"
	"NetworkClient/ClientUDP.hpp"
	"NetworkClient/ClientUDP.cpp"
	"NetworkClient/ClientTCP.hpp"
	"NetworkClient/ClientTCP.cpp"

	#Rendering
	"Rendering/MainPage.hpp"
	"Rendering/MainPage.cpp"

)


target_include_directories(r-type_client PUBLIC
	"${COMMON_LIB_DIR}"
	"${CONAN_INCLUDE_DIRS_SFML}"
)

message(CONAN_LIBS="${CONAN_LIBS}" c)

target_link_libraries(r-type_client PUBLIC
	"${CONAN_LIBS}"
	common_library
	game_ecs
)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
