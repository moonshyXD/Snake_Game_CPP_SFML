cmake_minimum_required(VERSION 3.28)
project(Snake_Game)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "D:/Snake_Game/lib/SFML/GCC 13.1.0 MinGW (SEH) - 64-bit/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

add_executable(Snake_Game main.cpp Snake.cpp)

target_link_libraries(Snake_Game sfml-graphics)