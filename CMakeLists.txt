cmake_minimum_required(VERSION 3.5)
project(RedCraft)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib
find_package(raylib REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add source files from the new structure
file(GLOB SOURCE
    src/main.cpp
    src/core/*.cpp
    src/terrain/*.cpp
    src/gui/*.cpp
    src/utils/*.cpp
    src/resources/*.cpp
)

file(GLOB BLOCKS
    src/blocks/*.cpp
)

# Combine all source files
set(ALL_SOURCES ${SOURCE} ${BLOCKS})

# Define the executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# Path to the Discord RPC library and include directories
set(DISCORD_RPC_INCLUDE_DIR /usr/include)
set(DISCORD_RPC_LIB_DIR /usr/lib)

include_directories(${DISCORD_RPC_INCLUDE_DIR})

# Link raylib, SDL2, and Discord RPC libraries
target_link_libraries(${PROJECT_NAME}
    raylib
    SDL2::SDL2
    ${DISCORD_RPC_LIB_DIR}/libdiscord-rpc.so
)

# Optionally, include directories for SDL2 if necessary
include_directories(${SDL2_INCLUDE_DIRS})

# Set library search path
link_directories(${DISCORD_RPC_LIB_DIR})

# Debugging flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
