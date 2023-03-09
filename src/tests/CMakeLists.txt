cmake_minimum_required(VERSION 3.0)

project(tests C)

enable_language(C)

add_executable(tests "test.c")

target_link_libraries(tests PRIVATE polymath)
target_include_directories(tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../library")