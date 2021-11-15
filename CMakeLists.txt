cmake_minimum_required(VERSION 3.6)
project(TowerDefense5)

# Set the language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/)

# Set the compiler flags
if(MSVC)
	message("Using MSVC!")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TowerDefense5)
else()
	message("Not using MSVC!")
	add_compile_options("-Wall" "-Wextra")
endif()

# Set the name of the executable to be produced
set(EXECUTABLE_NAME ${PROJECT_NAME})

set(SOURCES 
    src/main.cpp
    # add all other source files here as: src/<folder>/<filename>.cpp
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
