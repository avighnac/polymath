cmake_minimum_required(VERSION 3.5)

project(polymath)

enable_language(C)

set(ENABLE_TESTS ON CACHE BOOL "Enable tests")

add_subdirectory(src)

if (ENABLE_TESTS)
  add_subdirectory(tests)
endif ()