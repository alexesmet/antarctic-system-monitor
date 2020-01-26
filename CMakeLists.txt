cmake_minimum_required(VERSION 3.5)

project(antarctic-system-monitor)

add_subdirectory(backend/antarcticore-linux)
add_subdirectory(frontend/antarctic-qt)
include_directories(backend/antarcticore-linux)
