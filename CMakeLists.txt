cmake_minimum_required(VERSION 3.30)
project(ForzaV C)

set(CMAKE_C_STANDARD 23)

find_package(Curses REQUIRED)

add_executable(
        ForzaV
        main.c main.h
        src/sGame/sGame.c src/sGame/sGame.h
        src/vInstructions/vInstructions.c src/vInstructions/vInstructions.h
        src/vMain/vMain.c src/vMain/vMain.h
)

target_link_libraries(ForzaV PRIVATE ${CURSES_LIBRARIES})
target_include_directories(ForzaV PRIVATE ${CURSES_INCLUDE_DIRS})
