cmake_minimum_required(VERSION 3.16)
project(Spacefighter)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
        FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.0.0
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
        FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v4.2.2
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

add_executable(${PROJECT_NAME}
    source/audio.cpp
    source/game.cpp
    source/main.cpp
    source/projectile.cpp
    source/ship.cpp
    source/sprite.cpp
    source/textures.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib raylib_cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include ${raylib_INCLUDE_DIRS} ${raylib_cpp_INCLUDE_DIRS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

file(COPY sprites audio DESTINATION ${CMAKE_BINARY_DIR})