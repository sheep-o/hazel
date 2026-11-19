cmake_minimum_required(VERSION 4.4)

set(CMAKE_SYSTEM_NAME Generic-ELF)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/x86_64.cmake")

project(Hazel)

add_subdirectory(kernel)
