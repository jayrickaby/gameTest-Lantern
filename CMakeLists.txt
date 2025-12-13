cmake_minimum_required(VERSION 3.10)

project(gametest-lantern)

add_executable(gametest-lantern main.cpp)

install(TARGETS gametest-lantern RUNTIME DESTINATION bin)
