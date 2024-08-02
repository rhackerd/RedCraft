cmake_minimum_required(VERSION 3.3)
project(RedCraft)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib
find_package(raylib REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add source files
file(GLOB SOURCE src/*.cpp)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCE})

# Link raylib and SDL2 libraries
target_link_libraries(${PROJECT_NAME} raylib SDL2::SDL2)

# Optionally, include directories for SDL2 if necessary
include_directories(${SDL2_INCLUDE_DIRS})
