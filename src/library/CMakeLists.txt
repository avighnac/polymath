cmake_minimum_required(VERSION 3.0)

project(polymath)

enable_language(C)
enable_language(ASM_NASM)

# Enable all warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

set(cross_platform_sources
    cross_platform/plm_from_int.c
    cross_platform/plm_from_string.c
    cross_platform/plm_free.c
)

# set(linux_sources
#     linux/plm_from_int.asm
#     linux/plm_free.asm
# )

set(include_directories
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create an object library to be used by the static and shared libraries, this reduces code compile time.
# if (UNIX AND NOT APPLE)
#     set(cross_platform_sources ${linux_sources})
# endif()
add_library(objlib OBJECT ${cross_platform_sources})
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)
target_include_directories(objlib PRIVATE ${include_directories})

# Create the static library
add_library(polymath_static STATIC $<TARGET_OBJECTS:objlib>)
set_target_properties(polymath_static PROPERTIES OUTPUT_NAME polymath)

# Create the shared library
# add_library(polymath_shared SHARED $<TARGET_OBJECTS:objlib>)
# set_target_properties(polymath_shared PROPERTIES OUTPUT_NAME polymath)