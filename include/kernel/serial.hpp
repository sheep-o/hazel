#ifndef HAZEL_KERNEL_SERIAL_HPP_
#define HAZEL_KERNEL_SERIAL_HPP_

#include <stdint.h>
#include <io.hpp>
#include <printf.h>

namespace hzl::serial {

    constexpr uint16_t COM1 = 0x3F8;
    constexpr uint16_t COM2 = 0x2F8;
    constexpr uint16_t COM3 = 0x3E8;
    constexpr uint16_t COM4 = 0x2E8;
    constexpr uint16_t COM5 = 0x5F8;
    constexpr uint16_t COM6 = 0x4F8;
    constexpr uint16_t COM7 = 0x5E8;
    constexpr uint16_t COM8 = 0x4E8;

    #define IS_TRANSMIT_EMPTY(x) (inb(x + 5) & 0x20)

    bool init();
    void putc(const char c);
    void puts(const char *s);
    void log(const char* format, ...) ATTR_PRINTF(1, 2);
}


#endif