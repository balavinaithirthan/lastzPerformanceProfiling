cmake_minimum_required(VERSION 3.1)

project(bioinformatics-testing)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(library)
add_subdirectory(library)

add_executable(${PROJECT_NAME} main.cpp)
# 
target_link_libraries(${PROJECT_NAME} library)