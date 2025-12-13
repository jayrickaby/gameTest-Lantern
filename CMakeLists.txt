cmake_minimum_required(VERSION 3.16)

project(gametest-lantern)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(gametest-lantern main.cpp animation.cpp entity.cpp lantern.cpp light.cpp object.cpp player.cpp tilemap.cpp)

find_package(SFML 3.0 COMPONENTS Graphics Audio REQUIRED)

install(TARGETS gametest-lantern RUNTIME DESTINATION bin)

target_link_libraries(gametest-lantern PRIVATE SFML::Graphics SFML::Audio)

add_custom_command(TARGET gametest-lantern POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets
)
