cmake_minimum_required(VERSION 3.10)
project(StatStarters)

# Specify C++ standard for the target
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/term.cpp
)

# Add dependencies
add_subdirectory(external/cpr)
add_subdirectory(external/json)

# Create the executable
add_executable(StatStarters ${SOURCES})

# Link libraries
target_link_libraries(StatStarters PRIVATE cpr nlohmann_json::nlohmann_json)

# Find and link ncurses
find_package(Curses REQUIRED)
target_link_libraries(StatStarters PRIVATE ${CURSES_LIBRARIES})

# Add include directories
target_include_directories(StatStarters PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${CURSES_INCLUDE_DIR}
)