cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)
project("KETO")
include(FetchContent)

find_package(raylib QUIET)
if(NOT raylib_FOUND)
   FetchContent_Declare(
      raylib
      GIT_REPOSITORY https://github.com/raysan5/raylib.git
      GIT_TAG        master
      EXCLUDE_FROM_ALL
   )
   FetchContent_MakeAvailable(raylib)
endif()

file(GLOB SOURCES "src/*.cpp")

add_executable(keto.out ${SOURCES})

target_link_libraries(keto.out raylib)
target_include_directories(keto.out PRIVATE include ${raylib_SOURCE_DIR}/include)
target_compile_options(keto.out PRIVATE)
# target_compile_options(keto.out PRIVATE -Wall -Werror)

# cmake -B build && cmake --build build && ./build/keto.out
