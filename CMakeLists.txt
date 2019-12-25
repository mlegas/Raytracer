cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Raytracer LANGUAGES CXX)

include_directories(
        src
)

file(GLOB FILES
	src/*.cpp
	src/*.h)

add_library(RaytracingFiles SHARED ${FILES})

add_executable(Main
        src/Main.cpp
)

target_link_libraries(Main RaytracingFiles SDL2)
