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

# Přidejte cestu k Discord SDK
set(DISCORD_SDK_PATH "${CMAKE_SOURCE_DIR}/lib/discord_game_sdk")
include_directories(${DISCORD_SDK_PATH}/include)

# Nahraďte původní podmínku
if(EXISTS "${DISCORD_SDK_PATH}/include/discord_rpc.h")
    set(DISCORD_RPC_AVAILABLE TRUE)
    message(STATUS "Discord SDK nalezen v ${DISCORD_SDK_PATH}")
else()
    set(DISCORD_RPC_AVAILABLE FALSE)
    message(WARNING "Discord SDK nebyl nalezen v ${DISCORD_SDK_PATH}")
endif()

# Include directories for SDL2 if necessary
include_directories(${SDL2_INCLUDE_DIRS})

# Set library search path
link_directories(${DISCORD_RPC_LIB_DIR})

# Debugging flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Link raylib, SDL2, and Discord RPC libraries
target_link_libraries(${PROJECT_NAME}
    raylib
    SDL2::SDL2
)

if(DISCORD_RPC_AVAILABLE)
    if(UNIX AND NOT APPLE)
        set(DISCORD_LIB_PATH "${DISCORD_SDK_PATH}/lib/libdiscord-rpc.so")
    elseif(WIN32)
        set(DISCORD_LIB_PATH "${DISCORD_SDK_PATH}/lib/discord-rpc.dll")
    elseif(APPLE)
        set(DISCORD_LIB_PATH "${DISCORD_SDK_PATH}/lib/libdiscord-rpc.dylib")
    endif()
    
    if(EXISTS ${DISCORD_LIB_PATH})
        message(STATUS "Discord knihovna nalezena: ${DISCORD_LIB_PATH}")
        target_link_libraries(${PROJECT_NAME} ${DISCORD_LIB_PATH})
    else()
        message(WARNING "Discord knihovna nebyla nalezena v ${DISCORD_LIB_PATH}")
        set(DISCORD_RPC_AVAILABLE FALSE)
    endif()
endif()
