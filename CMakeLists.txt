cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

project(snake2)

find_package(raylib 5.0 QUIET)

include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(snake2 ${SRC_FILES})

target_link_libraries(snake2 raylib)
target_include_directories(snake2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)