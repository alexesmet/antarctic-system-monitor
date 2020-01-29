cmake_minimum_required(VERSION 3.5)

project(antarcticore-linux CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE antarcticore_linux_src *.cpp *.hpp)

add_library(antarcticore STATIC ${antarcticore_linux_src})
target_compile_options(antarcticore PRIVATE -Wall -Wextra -Wpedantic -Werror -fno-exceptions -fno-rtti)
set_target_properties(antarcticore PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(antarcticore
	PUBLIC include
	PRIVATE src
)
