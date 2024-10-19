cmake_minimum_required(VERSION 3.10)
project(Labyrinth_Project C)

set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.c")

# Executable
add_executable(Labyrinth ${SOURCES})

# Optional: Add tests
enable_testing()
add_subdirectory(tests)
