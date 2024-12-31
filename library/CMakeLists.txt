cmake_minimum_required(VERSION 3.1)

project(dummy_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SourceFiles src/helloworld.cpp)

add_library(${PROJECT_NAME} SHARED ${SourceFiles})

target_include_directories(${PROJECT_NAME} PUBLIC include)