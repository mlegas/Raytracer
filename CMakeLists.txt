cmake_minimum_required(VERSION 2.6)

project(Raytracer)

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
