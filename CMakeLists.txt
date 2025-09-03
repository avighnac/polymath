cmake_minimum_required(VERSION 3.10)

project(polymath LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_language(C)

set(ENABLE_TESTS ON CACHE BOOL "Enable tests")

add_subdirectory(src)

if (ENABLE_TESTS)
  add_subdirectory(tests)
endif ()