#ifndef __CPU_MC68030_REGISTER_H__
#define __CPU_MC68030_REGISTER_H__

#include <stdint.h>

struct mc68030_register {
    uint32_t d[8];
    uint32_t a[8];

    uint32_t pc;

    union {
        uint16_t raw;

        struct {
            uint8_t t : 2;
            uint8_t s : 1;
            uint8_t m : 1;
            uint8_t   : 1;
            uint8_t i : 3;

            struct {
                uint8_t   : 3;
                uint8_t x : 1;
                uint8_t n : 1;
                uint8_t z : 1;
                uint8_t v : 1;
                uint8_t c : 1;
            } ccr;
        };
    } sr;

    uint8_t sfc, dfc;

    uint32_t vbr;

    union {
        uint32_t raw;

        struct {
            uint32_t : 18;
            uint32_t walloc : 1;
            uint32_t dburen : 1;
            uint32_t dcclr : 1;
            uint32_t dceclr : 1;
            uint32_t dcfrz : 1;
            uint32_t dcen : 1;
            uint32_t : 3;
            uint32_t icclr : 1;
            uint32_t iceclr : 1;
            uint32_t icefrz : 1;
            uint32_t icen: 1;
        };
    } cacr;

    union {
        uint32_t raw;

        struct {
            uint32_t cfaddr : 24;
            uint32_t idx : 6;
            uint32_t : 2;
        };
    } caar;

    uint32_t usp, msp, isp;

    union {
        uint16_t raw;

        struct {
            uint16_t buserr : 1;
            uint16_t vlimit : 1;
            uint16_t svonly : 1;
            uint16_t : 1;
            uint16_t wp : 1;
            uint16_t invalid : 1;
            uint16_t modified : 1;
            uint16_t : 2;
            uint16_t taccess : 1;
            uint16_t : 3;
            uint16_t lvlcnt : 3;
        };
    } mmusr;

    union {
        uint64_t raw;

        struct {
            uint16_t range : 1;
            uint16_t limit : 15;
            uint16_t : 14;
            uint16_t type : 2;
            uint32_t addr;
        };
    } crp, srp;

    union {
        uint32_t raw;

        struct {
            uint16_t en : 1;
            uint16_t : 5;
            uint16_t srpen : 1;
            uint16_t fclen : 1;
            uint8_t pagesz;
            uint8_t inishft;
            uint8_t tblidx[4];
        };
    } tc;

    union {
        uint32_t raw;

        struct {
            uint8_t labase;
            uint8_t lamask;
            uint16_t en : 1;
            uint16_t : 4;
            uint16_t ci : 1;
            uint16_t rw : 1;
            uint16_t rwmask : 1;
            uint16_t : 1;
            uint16_t fcbase : 3;
            uint16_t : 1;
            uint16_t fcmask : 3;
        };
    } tt[2];
};

#endif  // __CPU_MC68030_REGISTER_H__
