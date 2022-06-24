    cmake_minimum_required(VERSION 3.10) # common to every CLion project
    project(PackMan) # project name

    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    find_package(glm REQUIRED)

    ADD_LIBRARY(lib
            scr/Carte.cpp
            scr/Enemy.cpp
            scr/MoveableSquare.cpp
            scr/Palette.cpp
            scr/Player.cpp
            scr/Square.cpp
            scr/Wall.cpp
            scr/glad.c
    )

    target_link_libraries(lib PUBLIC ${GLFW_LIBRARIES})

    add_executable(PackMan scr/main.cpp)
    target_link_libraries(PackMan lib)



