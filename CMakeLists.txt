cmake_minimum_required (VERSION 3.14)
project (TowerDefense5)

# Set the language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/)

# Define a grouping for source files in IDE project generation
# (for example Visual Studio solution filters)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Set the compiler flags
if(MSVC)
	message("Using MSVC!")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TowerDefense5)
else()
	message("Not using MSVC!")
	add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-O3")
endif()

# Build
# Include the directories for compilation
include_directories(include)
include_directories(src)

# Set the name of the executable to be produced
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(SOURCES 
    src/main.cpp
    src/Object.cpp
    src/Tower.cpp
    src/Enemy.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Include and link the SFML library
set(SFML_DIR "${PROJECT_SOURCE_DIR}/libs/SFML")
add_subdirectory(${SFML_DIR})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE sfml-audio sfml-graphics sfml-network sfml-system sfml-window)

# Include the json library
option(USE_EXTERNAL_JSON "Use an external JSON library" OFF)
if(USE_EXTERNAL_JSON)
  find_package(nlohmann_json 3.2.0 REQUIRED)
else()
  set(JSON_BuildTests OFF CACHE INTERNAL "")
  add_subdirectory("${PROJECT_SOURCE_DIR}/libs/json/")
endif()
target_link_libraries(${EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Include the TGUI library
set(TGUI_BACKEND SFML_GRAPHICS)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE tgui)
add_subdirectory("${PROJECT_SOURCE_DIR}/libs/TGUI/")

# Include GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Testing
enable_testing()
add_executable(
    run_tests
    src/Object.cpp
    src/Tower.cpp
    src/Enemy.cpp
    tests/ObjectTest.cpp
)
target_link_libraries(
    run_tests
    sfml-graphics
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)
