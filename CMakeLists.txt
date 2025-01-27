cmake_minimum_required(VERSION 3.1)

project(bioinformatics-testing)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_COMPILER "/usr/bin/gcc")


set(CMAKE_BUILD_TYPE Release)

add_subdirectory(library)

add_executable(${PROJECT_NAME} main.cpp lastz.cpp)

set(ENABLE_OPENMP FALSE)

if(ENABLE_OPENMP)
    find_package(OpenMP REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE library/include)
target_include_directories(${PROJECT_NAME} PRIVATE library)
target_link_libraries(${PROJECT_NAME} PUBLIC dummy_test)