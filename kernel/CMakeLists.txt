add_executable(kernel kmain.cpp boot/limine.cpp)

target_include_directories(kernel PRIVATE ../include/kernel)