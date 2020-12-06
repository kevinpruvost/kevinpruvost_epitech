# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_BINARY_DIR}")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (r-type_server
	main.cpp
	TcpServer.hpp
	TcpServer.cpp
	TcpClientManager.hpp
	TcpClientManager.cpp
	TcpClient.hpp
	TcpClient.cpp
	Room.hpp
	Room.cpp
	UdpServer.hpp
	UdpServer.cpp
	Player.hpp
	Player.cpp
)

target_include_directories(r-type_server PUBLIC
	"${COMMON_LIB_DIR}"
)

target_link_libraries(r-type_server PUBLIC
	#${BOOST_LIB}
	common_library
	game_ecs
	"${CONAN_LIBS}"
)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
