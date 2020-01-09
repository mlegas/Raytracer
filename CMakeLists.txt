cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Raytracer LANGUAGES CXX)

include_directories(
	include
	src
)

file(GLOB FILES
	src/*.cpp
	src/*.h)

list(FILTER FILES EXCLUDE REGEX ".*Main.cpp$")

if(MSVC)
  add_library(Raytracer STATIC ${FILES})
else()
  add_library(Raytracer SHARED ${FILES})
endif()

add_executable(Main
        src/Main.cpp
)

target_link_libraries(Main Raytracer SDL2)
