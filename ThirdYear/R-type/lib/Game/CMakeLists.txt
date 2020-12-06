# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(NOT CMAKE_C_COMPILE_OBJECT)
  set(CMAKE_C_COMPILE_OBJECT
    "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
endif()

add_library(game_ecs STATIC
    #Games Entity
    TitleScreen.cpp
    TitleScreen.hpp
    FpsDisplayer.cpp
    FpsDisplayer.hpp

    MenuPage/Background.hpp
    MenuPage/Background.cpp
    MenuPage/TextBar.hpp
    MenuPage/TextBar.cpp
    MenuPage/MenuAudio.hpp
    MenuPage/MenuAudio.cpp
    MenuPage/TextBarImage.hpp
    MenuPage/TextBarImage.cpp
    MenuPage/TextRoom.hpp
    MenuPage/TextRoom.cpp

    GamePage/Controller.cpp
    GamePage/Controller.hpp

    EntityInGame/InGamePlayer.hpp
    EntityInGame/InGamePlayer.cpp
    EntityInGame/InGameObstacle.cpp
    EntityInGame/InGameObstacle.cpp
    EntityInGame/InGameBoss.hpp
    EntityInGame/InGameBoss.cpp
    EntityInGame/InGameMonsterFactory.hpp
    EntityInGame/InGameMonsterFactory.cpp
    EntityInGame/InGameGenericMob.hpp
    EntityInGame/InGameGenericMob.cpp
)

target_link_libraries(game_ecs PUBLIC
    "${CROSS_COMPILE_LIB}"
    "${CONAN_LIBS}"
    common_library
)

target_include_directories(game_ecs PUBLIC
    "${CONAN_INCLUDE_DIRS_SFML}"
)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
