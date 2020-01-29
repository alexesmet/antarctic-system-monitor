cmake_minimum_required(VERSION 3.5)

project(antarctic-qt CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE antarctic_qt_src *.cpp *.hpp *.ui)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(antarctic-qt ${antarctic_qt_src})
target_compile_options(antarctic-qt PRIVATE -Wall -Wextra -Wpedantic -Werror -fno-exceptions -fno-rtti)
target_link_libraries(antarctic-qt Qt5::Widgets antarcticore)

