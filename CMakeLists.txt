cmake_minimum_required(VERSION 3.10)
project(StatStarters)

# Specify C++ standard for the target
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# Create the executable
add_executable(StatStarters ${SOURCES})

# Add include directories
target_include_directories(StatStarters PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${CURSES_INCLUDE_DIR}
)

# Add this line before `find_package(cpr REQUIRED)`
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} /opt/homebrew")  # Adjust path if necessary
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

# Find and link cpr and nlohmann_json
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

# Link libraries to the executable
target_link_libraries(StatStarters PRIVATE cpr::cpr nlohmann_json::nlohmann_json)