# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("R-Type" LANGUAGES CXX)

enable_testing()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

set(COMMON_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/)

if (UNIX)
    link_libraries(stdc++fs)
endif (UNIX)

INCLUDE_DIRECTORIES(
    ${CONAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/
    ${CMAKE_SOURCE_DIR}/lib/Network/
    ${ENGINE_DIRS}
    ${CMAKE_SOURCE_DIR}/lib/Engine/
    ${CMAKE_SOURCE_DIR}/lib/Components/
    ${CMAKE_SOURCE_DIR}/lib/Entities/
    ${CMAKE_SOURCE_DIR}/lib/Systems/
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(BOOST_LIB CONAN_PKG::boost)
    add_compile_options(/MD /W4 /D_WIN32_WINNT=0x0601)
else()
    set (BOOST_LIB CONAN_PKG::boost_asio)
    add_compile_options(-lpthread -fPIC -g -O3)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Incluez les sous-projets.
add_subdirectory ("lib")
add_subdirectory ("client")
add_subdirectory ("server")

message(${CMAKE_SOURCE_DIR})

if (EXISTS ${CMAKE_SOURCE_DIR}/benchmarks/googlebenchmarksetup/CMakeLists.txt)
    add_subdirectory ("benchmarks")
    add_subdirectory ("tests")
endif()