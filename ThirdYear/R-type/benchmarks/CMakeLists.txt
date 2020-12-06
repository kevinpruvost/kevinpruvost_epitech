# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_BINARY_DIR}")

find_package (Threads REQUIRED)

	add_subdirectory("googlebenchmarksetup")

	set(BENCHMARK_BIN_NAME r-type_benchmarks)

	add_executable ("${BENCHMARK_BIN_NAME}"
		"main.cpp"
	)

	target_include_directories("${BENCHMARK_BIN_NAME}" PUBLIC
		"${COMMON_LIB_DIR}"
	)

	target_link_libraries("${BENCHMARK_BIN_NAME}" PRIVATE
		"${CONAN_LIBS}"
		common_library
		Threads::Threads
		benchmark::benchmark
	)

	add_test(NAME "${BENCHMARK_BIN_NAME}" COMMAND "${BENCHMARK_BIN_NAME}")