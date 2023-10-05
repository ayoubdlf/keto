cmake_minimum_required(VERSION 3.26.4)
set(CMAKE_CXX_STANDARD 17)
project("KETO")

# Checking if raylib is install otherwise the cmake will
find_package(raylib REQUIRED)
if (NOT raylib_FOUND)
   include(FetchContent)

   FetchContent_Declare(
      raylib
      URL https://github.com/raysan5/raylib/archive/master.tar.gz
   )

   FetchContent_GetProperties(raylib)
   if (NOT raylib_POPULATED)
      FetchContent_Populate(raylib)
      add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
   endif()

endif()

file(GLOB SOURCES "src/*.cpp")

add_executable(keto.out ${SOURCES})

target_link_libraries(keto.out raylib)
target_include_directories(keto.out PRIVATE include ${raylib_SOURCE_DIR}/include)

# cmake -B build && cmake --build build && ./build/keto.out
