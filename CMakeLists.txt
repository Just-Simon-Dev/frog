cmake_minimum_required(VERSION 3.28)
project(frog)

# Find ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Define the executable
add_executable(frog main.cpp
        frog/frog_struct.cpp
        frog/frog_struct.h
        utils/map.cpp
        utils/map.h)

# Link the executable with the ncurses library
target_link_libraries(frog ${CURSES_LIBRARIES})
