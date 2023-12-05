cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)
project("KETO")
include(FetchContent)

# RAYLIB
find_package(raylib QUIET)
if(NOT raylib_FOUND)
   FetchContent_Declare(
      raylib
      GIT_REPOSITORY https://github.com/raysan5/raylib.git
      GIT_TAG        4.5.0
      EXCLUDE_FROM_ALL
   )
   FetchContent_MakeAvailable(raylib)
endif()

# JSON
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
   FetchContent_Declare(
      nlohmann_json
      GIT_REPOSITORY https://github.com/nlohmann/json.git
      GIT_TAG        v3.11.2
      EXCLUDE_FROM_ALL
   )
   FetchContent_MakeAvailable(nlohmann_json)
endif()


file(GLOB SOURCES "src/*.cpp")

add_executable(keto.out ${SOURCES})

target_link_libraries(keto.out raylib nlohmann_json::nlohmann_json)
target_include_directories(keto.out PRIVATE include ${raylib_SOURCE_DIR}/include)
target_compile_options(keto.out PRIVATE -Wall -Werror)

# cmake -B build && cmake --build build && ./build/keto.out
# cmake -B build && cmake --build build && valgrind ./build/keto.out --track-origins=yes --leak-check=full > log.txt 2>&1