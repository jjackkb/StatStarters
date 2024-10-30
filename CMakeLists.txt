cmake_minimum_required(VERSION 3.10)

project(StatStarters)

# add source files from the src directory
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(StatStarters ${SOURCES})

# add includes
target_include_directories(StatStarters PUBLIC ${CMAKE_SOURCE_DIR}/includes)
