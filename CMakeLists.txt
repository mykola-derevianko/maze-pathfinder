cmake_minimum_required(VERSION 3.29)
project(MazePathfinder)

set(CMAKE_CXX_STANDARD 20)

add_executable(MazePathfinder main.cpp Cell.cpp)
cmake_minimum_required(VERSION 3.24)
project(SFML_Game)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/libs/sfml/lib/cmake/SFML)
find_package(SFML COMPONENTS window graphics audio REQUIRED)

include_directories(C:/libs/sfml/include/SFML)
target_link_libraries(MazePathfinder sfml-window sfml-graphics sfml-audio)
