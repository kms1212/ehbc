#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

union srifmt {
    uint16_t raw;

    struct {
        uint16_t reg : 3;
        uint16_t op : 2;
        uint16_t risel : 1;
        uint16_t osz : 2;
        uint16_t dir : 1;
        uint16_t r_i : 3;
        uint16_t : 4;
    } ri;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t : 2;
        uint16_t dir : 1;
        uint16_t op : 2;
        uint16_t : 5;
    } ea;
};

/**
 * @brief MC68030: Disassemble shift / rotate instructions
 * Available instructions:
 * - ASL
 * - ASR
 * - LSL
 * - LSR
 * - ROXL
 * - ROXR
 * - ROL
 * - ROR
 */
DEF_OPFUNC(shiftrotate) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    union srifmt srfmt = { .raw = iwd[0] };

    if (srfmt.ri.osz == 0b11) {
        // use ea
        char dirind = srfmt.ea.dir ? 'L' : 'R';
        size_t wcur16 = 1;
        char eastr[20] = "";
            wcur16 = _mc68030_disasm_ext(
                iwd, isz16,
                0, srfmt.ea.eamode, srfmt.ea.eareg, wcur16,
                eastr, sizeof(eastr));

        switch (srfmt.ri.op) {
            case 0b00:
                snprintf(buf, len, "AS%c %s", dirind, eastr);
                break;
            case 0b01:
                snprintf(buf, len, "LS%c %s", dirind, eastr);
                break;
            case 0b10:
                snprintf(buf, len, "ROX%c %s", dirind, eastr);
                break;
            case 0b11:
                snprintf(buf, len, "RO%c %s", dirind, eastr);
                break;
        }
    } else {
        // use ri
        char dirind = srfmt.ri.dir ? 'L' : 'R';
        char riind = srfmt.ri.risel ? 'D' : '#';
        switch (srfmt.ri.op) {
            case 0b00:
                snprintf(buf, len, "AS%c D%d, %c%d", dirind, srfmt.ri.reg, riind, srfmt.ri.r_i);
                break;
            case 0b01:
                snprintf(buf, len, "LS%c D%d, %c%d", dirind, srfmt.ri.reg, riind, srfmt.ri.r_i);
                break;
            case 0b10:
                snprintf(buf, len, "ROX%c D%d, %c%d", dirind, srfmt.ri.reg, riind, srfmt.ri.r_i);
                break;
            case 0b11:
                snprintf(buf, len, "RO%c D%d, %c%d", dirind, srfmt.ri.reg, riind, srfmt.ri.r_i);
                break;
        }
    }

    return 1;
}
