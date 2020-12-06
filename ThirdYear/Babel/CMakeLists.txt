# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("Babel" LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP(TARGETS)
INCLUDE_DIRECTORIES(
    ${CONAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/
    ${CMAKE_SOURCE_DIR}/lib/Babel/
)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Gui     REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
endif (MSVC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Incluez les sous-projets.
#add_subdirectory ("lib")
add_subdirectory ("client")
add_subdirectory ("server")
