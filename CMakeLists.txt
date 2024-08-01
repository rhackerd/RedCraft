cmake_minimum_required(VERSION 3.3)
project(RedCraft)




set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(raylib REQUIRED)
find_package(glm REQUIRED)

file(GLOB SOURCE src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} glm)
