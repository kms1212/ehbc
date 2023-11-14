#include "dbgutils.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "types.h"

void hexdump(const void* p, size_t len, uint8_t option) {
    if (p == NULL) return;

    size_t address = 0, row = 0;

    while (1) {
        if (address >= len) break;
        size_t nread = ((len - address) > 16) ? 16 : (len - address);

        // Print Address
        fprintf(stderr, "%016"PRIX64" ", (uint64_t)address);

        // Show the hex codes
        for (size_t i = 0; i < 16; i++) {
            if (i % 8 == 0) fputc(' ', stderr);
            if (i < nread)
                fprintf(stderr, " %02X", ((uint8_t*)p)[16 * row + i]);
            else
                fprintf(stderr, "   ");
        }

        // Show printable characters
        fputc(' ', stderr);
        for (size_t i = 0; i < nread; i++) {
            uint8_t ch = ((uint8_t*)p)[16 * row + i];
            if (ch < 32 || ch > 126) fputc('.', stderr);
            else
                fputc(ch, stderr);
        }

        fputc('\n', stderr);
        address += 16;
        row++;
    }
}

int dbgshell(FILE* istream, FILE* ostream) {
    fprintf(ostream, "dbg> ");

    char cmdstr[256];
    fgets(cmdstr, sizeof(cmdstr), istream);

    return 0;
}
