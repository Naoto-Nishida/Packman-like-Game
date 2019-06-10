cmake_minimum_required(VERSION 3.10)

project(glut_game C)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 11)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_BINARY_DIR}")

# cmake -DCMAKE_BUILD_TYPE=
set(CMAKE_C_FLAGS "-std=c11 -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

add_executable(MyInvaderGame.out main.c display.c draw.c init.c load_tex.c motion.c mouse.c resize.c xorshift.c)

target_link_libraries(MyInvaderGame.out -lGL -lglut)
