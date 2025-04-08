cmake_minimum_required(VERSION 3.24)
project(MazePathfinder)

set(CMAKE_CXX_STANDARD 20)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/libs/sfml/lib/cmake/SFML)

find_package(SFML COMPONENTS window graphics audio REQUIRED)

add_executable(MazePathfinder main.cpp Cell.cpp)
project(MazePathfinder)

include_directories(C:/libs/sfml/include/SFML)
target_link_libraries(MazePathfinder sfml-window sfml-graphics sfml-audio)
