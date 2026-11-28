add_executable(kernel kmain.cpp boot/limine.cpp
    io.cpp
    serial.cpp
    printf.cpp)

target_include_directories(kernel PRIVATE ../include/kernel)