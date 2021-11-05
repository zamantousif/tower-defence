cmake_minimum_required (VERSION 3.10)
project (TowerDefense5)

# Set the language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Set the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -O3")

# Build
# Include the directories for compilation
include_directories(include)
include_directories(src)
# Set the name of the executable to be produced
set(EXECUTABLE_NAME towerdefense5)
set(SOURCES 
    src/main.cpp
    # add all other source files here as: src/<folder>/<filename>.cpp
)
# Add all .cpp - files under src/ directory
add_executable(${EXECUTABLE_NAME} ${SOURCES})
set(CMAKE_BUILD_TYPE Debug)

# Find Box2D library
# find_package(Box2D REQUIRED)
# target_link_libraries(${EXECUTABLE_NAME} Box2D)

# If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

# In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "/home/mtz/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/mtz/SFML-2.5.1/include/lib")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

#SFML
find_package(SFML 2.5 COMPONENTS audio graphics network system window REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} sfml-audio sfml-graphics sfml-network sfml-system sfml-window)

# For installing targets (not mandatory)
# install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
