# CMake minimum required version (3.10+)
cmake_minimum_required(VERSION 3.10)

project(PokemonGame)

# C++11 is required
set(CMAKE_CXX_STANDARD 11)

# source and include directories
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(DATA_DIR ${CMAKE_SOURCE_DIR}/data)

include_directories(${INCLUDE_DIR})
set(SOURCE_FILES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/game.cpp
    ${SOURCE_DIR}/held_item.cpp
    ${SOURCE_DIR}/move.cpp
    ${SOURCE_DIR}/player.cpp
    ${SOURCE_DIR}/pokemon.cpp
    ${SOURCE_DIR}/solve.cpp
)

# after building, the executable's name will be "pokemonGame"
add_executable(pokemonGame ${SOURCE_FILES})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_command(TARGET pokemonGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${DATA_DIR} ${CMAKE_BINARY_DIR}/data
)