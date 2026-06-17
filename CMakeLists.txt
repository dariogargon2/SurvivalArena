cmake_minimum_required(VERSION 3.16)

project(SurvivalArena)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:/SFML-3.0.2-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.2/lib/cmake/SFML")

add_executable(SurvivalArena
    main.cpp
    src/Player.cpp
    src/Enemy.cpp
)

target_include_directories(SurvivalArena PRIVATE include)

find_package(SFML REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(SurvivalArena PRIVATE 
    SFML::Graphics
    SFML::Window
    SFML::System
)