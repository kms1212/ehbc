#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "cpu/mc68030/_operation.h"
#include "cpu/cpu.h"


#include "log.h"
void _lprintf(enum loglevel lvl, const char* iden, const char* fmt, ...) {
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    vfprintf(stderr, fmt, arg_ptr);
}


ssize_t mc68030_disasm(uint16_t* iwd, size_t isz16, char* buf, size_t len);

int main(int argc, char** argv) {
    size_t addr;
    for (;;) {
        uint16_t opcode[4];
        char asmbuf[50];

        printf("%08zx > ", addr);

        ssize_t advcnt;
        int widx = 0;
        do {
            if (scanf("%hX", &(opcode[widx])) < 1) return 0;
            widx++;
        } while ((advcnt = mc68030_disasm(opcode, widx, asmbuf, sizeof(asmbuf))) == IE_NELEN);
        fflush(stdin);

        printf("%08zx: ", addr);

        switch (advcnt) {
            case IE_ERR:
                printf("Decode error                                      ");
                break;
            case IE_UNKNOWN:
                printf("Unknown instruction                               ");
                break;
            case IE_INVALID:
                printf("Invalid instruction                               ");
                break;
            default:
                if (advcnt > 0) {
                    printf("%s", asmbuf);
                    addr += advcnt * 2;
                    size_t tlen = sizeof(asmbuf) - strnlen(asmbuf, sizeof(asmbuf));
                    for (; tlen > 0; tlen--) putc(' ', stdout);
                }
                break;
        }

        for (int j = 0; j < widx; j++)
            printf("0x%04X ", opcode[j]);
        putc('\n', stdout);
    }
    return 0;
}
