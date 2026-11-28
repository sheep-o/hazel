#include <cstdint>
#include <boot/limine.h>
#include <serial.hpp>

extern volatile uint64_t limine_base_revision[3];
extern volatile limine_framebuffer_request framebuffer_request;
extern volatile limine_memmap_request memmap_request;
extern volatile limine_hhdm_request hhdm_request;


[[noreturn]] static void halt() {
    for (;;) {
        __asm__ volatile("cli; hlt");
    }
}


extern "C" void kmain() {
    if (!LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision)) {
        halt();
    }

    if (!framebuffer_request.response || 
        !memmap_request.response || 
        !hhdm_request.response) {
        halt();
    }

    const auto *memmap = memmap_request.response;
    for (uint64_t i = 0; i < memmap->entry_count; i++) {
        const auto *entry = memmap->entries[i];
        if (entry->type == LIMINE_MEMMAP_USABLE) {
            // setup memory stuff
        }
    }

    hzl::serial::init();
    hzl::serial::log("\n\nHello world: %08X\n", 0x1337);

    halt();
}
