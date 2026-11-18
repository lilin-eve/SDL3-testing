#   Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.23)

#   Define the project
project(
    SDL3-testing
    VERSION 1.0
    DESCRIPTION "My first SDL3 project."
    LANGUAGES CXX
)

#   Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(
    CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

add_executable(SDL3-testing
    src/main.cpp
    src/ErrorHandling.cpp
)

if(APPLE)
    set_target_properties(SDL3-testing PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path"
    BUILD_WITH_INSTALL_RPATH TRUE 
    MACOSX_RPATH TRUE 
    )
elseif(UNIX)
    set_target_properties(SDL3-testing PROPERTIES 
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE 
    )
endif()

#include_directories(/opt/homebrew/include)
#link_directories(/opt/homebrew/lib)


#set(SOURCES src/main.cpp ${/opt/homebrew/include/SDL3}/SDL.h $ )

#target_include_directories(SDL3-project PRIVATE ${/opt/homebrew/include} )

#   Specify we want to build SDL_TTF's dependencies
set(SDLTTF_VENDORED ON)

#   Set variable for local directory 'vendor/'
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")

add_subdirectory(${VENDOR_DIR}/SDL)
add_subdirectory(${VENDOR_DIR}/SDL_image)
add_subdirectory(${VENDOR_DIR}/SDL_ttf)

#find_package(SDL3 REQUIRED)
#find_package(SDL3_image REQUIRED)
#find_package(SDL3_ttf REQUIRED)

target_link_libraries(SDL3-testing
    SDL3::SDL3 
    SDL3_image::SDL3_image 
    SDL3_ttf::SDL3_ttf
)
