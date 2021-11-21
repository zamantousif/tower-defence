cmake_minimum_required (VERSION 3.14)
project (TowerDefense5)

# Set the language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Set the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -O3")

# Build
# Include the directories for compilation
include_directories(include)
include_directories(src)
# Set the name of the executable to be produced
set(EXECUTABLE_NAME towerdefense5)
set(SOURCES 
    src/main.cpp
    src/Object.cpp
)
# Add all .cpp - files under src/ directory
add_executable(${EXECUTABLE_NAME} ${SOURCES})
set(CMAKE_BUILD_TYPE Debug)

# Support external libraries
# SFML
# If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)
# In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
set(SFML_INCLUDE_DIR /libs/SFML/include)
set(SFML_LIBRARY_DIR /libs/SFML/src)
link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
# find_package(SFML 2.5 COMPONENTS audio graphics network system window REQUIRED)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Linking
target_link_libraries(${EXECUTABLE_NAME} PRIVATE sfml-audio sfml-graphics sfml-network sfml-system sfml-window)

# For installing targets (not mandatory)
# install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# Testing
enable_testing()
add_executable(
    run_tests
    src/Object.cpp
    tests/test.cc
)
target_link_libraries(
    run_tests
    sfml-graphics
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)
