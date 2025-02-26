cmake_minimum_required(VERSION 3.5)

project(polymath_tests)

enable_language(CXX)

# Download and build Google Test if necessary
if(NOT TARGET gtest)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.13.0
    )

    FetchContent_GetProperties(googletest)

    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    endif()
endif()

# Add test sources
set(test_sources
    from_base10_string_tests.cpp
    to_base10_string_tests.cpp
    add_whole_tests.cpp
    from_unsigned_long_long_tests.cpp
    subtract_whole_tests.cpp
    multiply_whole_tests.cpp
)

add_executable(${PROJECT_NAME} ${test_sources})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main polymath_static m)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
