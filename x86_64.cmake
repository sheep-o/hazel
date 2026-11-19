set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CXX clang++)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_CFLAGS "-std=c++20 \
                      -ffreestanding \
                      -fno-exceptions \
                      -fno-rtti \
                      -fno-stack-protector \
                      -fno-pic \
                      -mno-redzone \
                      -mno-sse \
                      -mno-sse2 \
                      -mno-mmx \
                      -mcmodel=kernel \
                      -Wall -Wextra -Werror \
                      -g \
                      --target=x86_64-unknown-elf")
set(CMAKE_EXE_LINKER_FLAGS "-ffreestanding -nostdlib -T ${CMAKE_CURRENT_SOURCE_DIR}/x86_64.ld --target=x86_64-unknown-elf")
