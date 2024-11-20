cmake_minimum_required(VERSION 3.11)
project(StatStarters)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Main.cc
    ${CMAKE_SOURCE_DIR}/src/App.cc
    ${CMAKE_SOURCE_DIR}/src/ErrorHandler.cc
    ${CMAKE_SOURCE_DIR}/src/FantasyApi/Fantasy.cc
    ${CMAKE_SOURCE_DIR}/src/FantasyApi/Api.cc
    ${CMAKE_SOURCE_DIR}/src/Objects/League.cc
    ${CMAKE_SOURCE_DIR}/src/Objects/Member.cc
    ${CMAKE_SOURCE_DIR}/src/Objects/Player.cc
    ${CMAKE_SOURCE_DIR}/src/UI/Ui.cc
    ${CMAKE_SOURCE_DIR}/src/UI/ProcessComm.cc
    ${CMAKE_SOURCE_DIR}/src/UI/DisplayOutput.cc
   
    ${CMAKE_SOURCE_DIR}/includes/Main.h
    ${CMAKE_SOURCE_DIR}/includes/App.h
    ${CMAKE_SOURCE_DIR}/includes/ErrorHandler.h
    ${CMAKE_SOURCE_DIR}/includes/Fantasy.h
    ${CMAKE_SOURCE_DIR}/includes/Api.h
    ${CMAKE_SOURCE_DIR}/includes/League.h
    ${CMAKE_SOURCE_DIR}/includes/Member.h
    ${CMAKE_SOURCE_DIR}/includes/Player.h
    ${CMAKE_SOURCE_DIR}/includes/Ui.h
    ${CMAKE_SOURCE_DIR}/includes/ProcessComm.h
    ${CMAKE_SOURCE_DIR}/includes/DisplayOutput.h
)

# Create the executable
add_executable(StatStarters ${SOURCES})

# Add include directories
target_include_directories(StatStarters PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
)

# FetchContent for dependencies
include(FetchContent)

# Fetch cpr
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.4
)
FetchContent_MakeAvailable(cpr)

# Fetch nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Find and link ncurses
find_library(NCURSES_LIBRARY ncurses REQUIRED)
if(NCURSES_LIBRARY)
    message(STATUS "Found ncurses: ${NCURSES_LIBRARY}")
else()
    message(FATAL_ERROR "ncurses library not found")
endif()

# Link libraries
find_library(CORESERVICES CoreServices)
target_link_libraries(StatStarters PRIVATE cpr::cpr nlohmann_json::nlohmann_json ${CORESERVICES} ${NCURSES_LIBRARY})