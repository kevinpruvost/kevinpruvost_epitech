# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_BINARY_DIR}")

find_package (Threads REQUIRED)

set(UNIT_TESTS_BIN_NAME r-type_unit_tests)

if(NOT CMAKE_C_COMPILE_OBJECT)
  set(CMAKE_C_COMPILE_OBJECT
    "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
endif()

if (MSVC)
    set(CROSS_COMPILE_FILE
        ../lib/FileSystemWatcher/windows_get_current_path.c)
else()
    set(CROSS_COMPILE_FILE
        ../lib/FileSystemWatcher/linux_get_current_path.c)
endif()

add_library(testDLLoader SHARED
    DLLoader/TestClass.cpp
    DLLoader/TestClass.hpp
	../lib/Engine/Entity.cpp
	../lib/Engine/EntityIdFactory.cpp
	../lib/DebugController.cpp
    ../lib/Engine/Component.cpp
    ../lib/Engine/EntitySignature.cpp
)

add_executable ("${UNIT_TESTS_BIN_NAME}"
	"${CROSS_COMPILE_FILE}"
	
	main.cpp

	Engine/TestComponent.hpp
	Engine/TestSystem.hpp
	Engine/TestEntity.hpp
	Engine/ColliderTest.hpp
)

set_property(TARGET "${UNIT_TESTS_BIN_NAME}" PROPERTY CXX_STANDARD 17)

target_include_directories("${UNIT_TESTS_BIN_NAME}" PUBLIC
	"${COMMON_LIB_DIR}"
)

target_link_libraries("${UNIT_TESTS_BIN_NAME}" PUBLIC
	"${CONAN_LIBS}"
	common_library
	game_ecs
	gtest
	Threads::Threads
)

add_test(NAME "${UNIT_TESTS_BIN_NAME}"
		 COMMAND "${UNIT_TESTS_BIN_NAME}")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
