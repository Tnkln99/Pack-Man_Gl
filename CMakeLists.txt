    cmake_minimum_required(VERSION 3.10) # common to every CLion project
    project(PackMan) # project name

    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)

    ADD_LIBRARY(ola
            scr/Carte.cpp
            scr/Enemy.cpp
            scr/MoveableSquare.cpp
            scr/Palette.cpp
            scr/Player.cpp
            scr/Square.cpp
            scr/Wall.cpp
            scr/glad.c
    )

    target_link_libraries(ola -lglfw -ldl)

    add_executable(PackMan scr/main.cpp)
    target_link_libraries(PackMan ola)



