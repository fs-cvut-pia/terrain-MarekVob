cmake_minimum_required(VERSION 3.0)
project(PIA_terrain)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(findpath main.cpp Path.cpp TerrainMap.cpp Airplane.cpp Boat.cpp Road.cpp)