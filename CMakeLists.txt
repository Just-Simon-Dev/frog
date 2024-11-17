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
        utils/map.h
        config.h)

# Link the executable with the ncurses library
target_link_libraries(frog ${CURSES_LIBRARIES})


# Add a custom target to run the program
add_custom_target(run
        COMMAND frog
        DEPENDS frog
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running the frog program"
)