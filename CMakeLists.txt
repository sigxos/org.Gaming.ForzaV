cmake_minimum_required(VERSION 3.30)
project(ForzaV C)

set(CMAKE_C_STANDARD 23)

find_package(Curses REQUIRED)

add_executable(ForzaV main.c
        src/menu/view-menu/view-menu.c
        src/menu/view-menu/view-menu.h
        src/game/start-game/start-game.c
        src/game/start-game/start-game.h
        main.h)

target_link_libraries(ForzaV PRIVATE ${CURSES_LIBRARIES})
target_include_directories(ForzaV PRIVATE ${CURSES_INCLUDE_DIRS})
