cmake_minimum_required(VERSION 3.5)

project(polymath)

enable_language(C)
# enable_language(ASM_NASM)

# Enable all warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

set(cross_platform_sources
    init_dest/plm_from_int.c
    init_dest/plm_from_long.c
    init_dest/plm_from_long_long.c
    init_dest/plm_from_unsigned_long_long.c
    init_dest/plm_from_base10_string.c
    init_dest/plm_from_plm.c
    init_dest/plm_to_base10_string.c
    init_dest/plm_free.c

    arithmetic/plm_add_whole.c
    arithmetic/plm_subtract_whole.c
    arithmetic/plm_multiply_whole.c

    arithmetic/plm_shl.c
    arithmetic/plm_shr.c
    arithmetic/plm_rtz.c
    arithmetic/plm_multiply.c
    arithmetic/plm_add.c
    arithmetic/plm_subtract.c
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
add_library(polymath_objlib OBJECT ${cross_platform_sources})
set_property(TARGET polymath_objlib PROPERTY POSITION_INDEPENDENT_CODE 1)
target_include_directories(polymath_objlib PRIVATE ${include_directories})

# Create the static library
add_library(polymath_static STATIC $<TARGET_OBJECTS:polymath_objlib>)
set_target_properties(polymath_static PROPERTIES OUTPUT_NAME polymath)

# Create the shared library
# add_library(polymath_shared SHARED $<TARGET_OBJECTS:polymath_objlib>)
# set_target_properties(polymath_shared PROPERTIES OUTPUT_NAME polymath)