#define LOG_IDEN "main"

#include "emulator.h"

#include <stdbool.h>
#include <string.h>

#include "params.h"
#include "error.h"
#include "memory/memory.h"
#include "log.h"
#include "compat.h"
#include "cpu/cpu.h"

void* emulator_main(void* arg) {
    struct memory* mem = init_memory("../fwcode/build/fw.bin", true, 256, 256, true);
    lprintf(LL_DEBUG, "Memory Initialized");

    uint16_t buf[11];
    char asmbuf[50];
    size_t ilen = 0;
    int fret = 0;

    for (size_t cur = 1024; cur < 1536;) {
        ilen = 0;

        do {
            read16_memory(mem, cur, &(buf[ilen]));
            lprintf(LL_DEBUG, "%0X", buf[ilen]);
            cur += sizeof(uint16_t);
            ilen++;
        } while ((fret = mc68030_disasm(buf, ilen, asmbuf, sizeof(asmbuf))) == IE_NELEN);

        if (fret > 0) {
            lprintf(LL_DEBUG, "%08X: %s", cur - ilen * sizeof(uint16_t), asmbuf);
        } else {
            lprintf(LL_ERROR, "Unable to disassemble");
        }
    }

    deinit_memory(mem);
    lprintf(LL_DEBUG, "Memory Denitialized");

    exit_thread(NULL);
    return NULL;
}
