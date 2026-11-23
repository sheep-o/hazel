cmake_minimum_required(VERSION 3.10)

set(CMAKE_SYSTEM_NAME Generic-ELF)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/x86_64.cmake")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(Hazel)

add_subdirectory(kernel)

set(LIMINE_DIR "${CMAKE_SOURCE_DIR}/limine-binary")
set(ISO_ROOT "${CMAKE_BINARY_DIR}/iso_root")
set(ISO_FILE "${CMAKE_BINARY_DIR}/hazel.iso")

find_program(XORRISO xorriso REQUIRED)
find_program(QEMU qemu-system-x86_64 REQUIRED)

add_custom_command(
    OUTPUT "${ISO_FILE}"

    COMMAND ${CMAKE_COMMAND} -E rm -rf "${ISO_ROOT}"

    COMMAND ${CMAKE_COMMAND} -E make_directory
        "${ISO_ROOT}/boot/limine"
        "${ISO_ROOT}/EFI/BOOT"

    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:kernel>"
        "${ISO_ROOT}/boot/kernel.elf"

    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/limine.conf"
        "${ISO_ROOT}/boot/limine/limine.conf"

    COMMAND ${CMAKE_COMMAND} -E copy
        "${LIMINE_DIR}/limine-uefi-cd.bin"
        "${ISO_ROOT}/boot/limine/limine-uefi-cd.bin"

    COMMAND ${CMAKE_COMMAND} -E copy
        "${LIMINE_DIR}/BOOTX64.EFI"
        "${ISO_ROOT}/EFI/BOOT/BOOTX64.EFI"

    COMMAND ${XORRISO}
        -as mkisofs
        -R -r -J
        --efi-boot boot/limine/limine-uefi-cd.bin
        -efi-boot-part
        --efi-boot-image
        --protective-msdos-label
        -o "${ISO_FILE}"
        "${ISO_ROOT}"

    DEPENDS
        kernel
        "${CMAKE_SOURCE_DIR}/limine.conf"
        "${LIMINE_DIR}/limine-uefi-cd.bin"
        "${LIMINE_DIR}/BOOTX64.EFI"

    VERBATIM
)

add_custom_target(iso DEPENDS "${ISO_FILE}")

set(OVMF_CODE
    "/usr/share/OVMF/OVMF_CODE_4M.fd"
    CACHE FILEPATH "OVMF UEFI firmware"
)

add_custom_target(run
    COMMAND ${QEMU}
        -m 512M
        -machine q35
        -drive
            "if=pflash,format=raw,readonly=on,file=${OVMF_CODE}"
        -cdrom "${ISO_FILE}"
        -serial stdio
        -no-reboot

    DEPENDS iso
)