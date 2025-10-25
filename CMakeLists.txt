cmake_minimum_required(VERSION 3.10)

project(C4 C)

# if(NOT CMAKE_C_STANDARD)
    # set(CMAKE_C_STANDARD 99)
# endif()

set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(vendor/libatomic_ops)
add_subdirectory(vendor/bdwgc)

include_directories(src)

set(PROJECT_SOURCES
    src/throwException.c
    src/Pointer.c
    src/Array.c
    src/Person.c
    test.c
)

add_executable(c4_test ${PROJECT_SOURCES})

target_link_libraries(c4_test PRIVATE gc)
target_include_directories(c4_test PRIVATE vendor/bdwgc/include)
