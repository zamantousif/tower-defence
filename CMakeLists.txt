cmake_minimum_required(VERSION 3.14)
project(TowerDefense5)

# Set the language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# Define a grouping for source files in IDE project generation
# (for example Visual Studio solution filters)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
# ------------------------------Compiler Flags----------------------------------
# Set the compiler flags
if(MSVC)
	message("Using MSVC!")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TowerDefense5)
else()
	message("Not using MSVC!")
	add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-O3")
endif()

# ----------------------------------Build---------------------------------------
# Include the directories for compilation
include_directories(include)
include_directories(src)
# Set the name of the executable to be produced
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(SOURCES 
    src/main.cpp
    include/types.hpp
    src/logic/object.cpp
    include/object.hpp
    include/basic_tower.hpp
    include/bomb_projectile.hpp
    include/bomb_tower.hpp
    include/high_damage_tower.hpp
    include/melting_tower.hpp
    include/slowing_tower.hpp
    include/thorn_eruptor.hpp
    src/logic/towers/tower.cpp
    src/logic/towers/basic_tower.cpp
    src/logic/towers/slowing_tower.cpp
    src/logic/towers/high_damage_tower.cpp
    src/logic/towers/melting_tower.cpp
    src/logic/towers/bomb_tower.cpp
    src/logic/towers/thorn_eruptor.cpp
    include/tower.hpp
    src/logic/enemies/enemy.cpp
    include/enemy.hpp
    src/logic/projectiles/projectile.cpp
    src/logic/projectiles/bomb_projectile.cpp
    include/projectile.hpp
    src/logic/enemies/splitworm.cpp
    include/splitworm.hpp
    src/logic/application.cpp
    include/application.hpp
    src/logic/game.cpp
    include/game.hpp
    src/logic/map.cpp
    include/map.hpp
    src/logic/collision.cpp
    include/collision.hpp
    include/constants.hpp
)

# ---------------------------------Targets--------------------------------------
add_executable(${EXECUTABLE_NAME} ${SOURCES})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# ----------------------------External Libraries--------------------------------
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
    GIT_REPOSITORY https://github.com/google/googletest.git # URL of repository
    GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929 # hash of the commit
    SOURCE_DIR libs/googletest # path to library inside build
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---------------------------------Testing--------------------------------------
enable_testing()
set(TESTS_EXE_NAME ${PROJECT_NAME}_tests)
add_executable(
    ${TESTS_EXE_NAME}
    src/logic/object.cpp
    src/logic/towers/tower.cpp
    src/logic/enemies/enemy.cpp
    src/logic/projectiles/projectile.cpp
    src/logic/collision.cpp
    tests/main.cpp
    tests/collision_test.cpp
)
target_link_libraries(
    ${TESTS_EXE_NAME}
    sfml-graphics
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TESTS_EXE_NAME})

# ------------------------------Documentation-----------------------------------
option(BUILD_DOC "Build documentation" ON)
# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_EXCLUDE_PATTERNS
        *test.cpp
    )
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
