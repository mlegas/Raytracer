cmake_minimum_required(VERSION 2.6)

project(Raytracer)

include_directories(
	source
)

file(GLOB FILES
	source/*.cpp
	source/*.h)

add_library(RaytracingFiles SHARED ${FILES})

add_executable(Main
	Main.cpp
)

target_link_libraries(Main RaytracingFiles glm SDL2)