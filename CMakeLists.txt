cmake_minimum_required(VERSION 3.11)
project(StatStarters)

# Specify C++ standard for the target
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/App.cpp
    ${CMAKE_SOURCE_DIR}/src/ErrorHandler.cpp 
    ${CMAKE_SOURCE_DIR}/src/ESPNFantasyAPI.cpp
    ${CMAKE_SOURCE_DIR}/src/League.cpp
    ${CMAKE_SOURCE_DIR}/src/Member.cpp
    )

# Create the executable
add_executable(StatStarters ${SOURCES})

# Add include directories
target_include_directories(StatStarters PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${CURSES_INCLUDE_DIR}
)

# Include FetchContent module
include(FetchContent)

# Fetch cpr
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.4  # Replace with the desired version
)
FetchContent_MakeAvailable(cpr)

# Fetch nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2  # Replace with the desired version
)
FetchContent_MakeAvailable(nlohmann_json)

# Link libraries to the executable
find_library(CORESERVICES CoreServices)
target_link_libraries(StatStarters PRIVATE cpr::cpr nlohmann_json::nlohmann_json ${CORESERVICES})