cmake_minimum_required(VERSION 3.10)

set(CMAKE_SYSTEM_NAME Generic-ELF)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/x86_64.cmake")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(Hazel)

add_subdirectory(kernel)