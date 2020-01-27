cmake_minimum_required(VERSION 3.5)

project(antarctic-system-monitor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(antarctic-system-monitor
    gui/main.cpp
    core/processes.h
    core/allpids.h
    gui/mainwindow.cpp
    gui/mainwindow.h
    gui/mainwindow.ui
  )

target_link_libraries(antarctic-system-monitor PRIVATE Qt5::Widgets)
