cmake_minimum_required(VERSION 3.25)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings shared by every target
add_library(raytracer_warnings INTERFACE)
if(MSVC)
    target_compile_options(raytracer_warnings INTERFACE /W4)
else()
    target_compile_options(raytracer_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

# The code lives in a library so that both the program and the tests use it
add_library(raytracer_core src/greeting.cpp src/vector.cpp)
target_include_directories(raytracer_core PUBLIC src)
target_link_libraries(raytracer_core PRIVATE raytracer_warnings)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core raytracer_warnings)

add_custom_target(run COMMAND raytracer DEPENDS raytracer USES_TERMINAL)

option(RAYTRACER_BUILD_TESTS "Build the tests" ON)
if(RAYTRACER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
