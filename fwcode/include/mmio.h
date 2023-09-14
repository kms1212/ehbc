#ifndef __MMIO_H__
#define __MMIO_H__

#include "types.h"
#include "smc.h"

#define DEFINE_MMIO_DEV(name)   static struct mmio_dev name = 
#define BASE(addr)              (ptr_t)addr
#define ADDRWIDTH(width)        width
#define CSID(cs_id)             cs_id


struct mmio_dev {
    ptr_t       base_addr;
    uint8_t     addr_width;
    uint8_t     cs_id;
};

DEFINE_MMIO_DEV(fwmc)           { BASE(0x00000000), ADDRWIDTH(22), CSID(0)  };
DEFINE_MMIO_DEV(smc)            { BASE(0xFFFFFFFE), ADDRWIDTH(1),  CSID(1)  };
DEFINE_MMIO_DEV(fpu)            { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(2)  };
DEFINE_MMIO_DEV(dram)           { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(3)  };
DEFINE_MMIO_DEV(dramcfg)        { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(4)  };
DEFINE_MMIO_DEV(dmac)           { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(5)  };
DEFINE_MMIO_DEV(pic)            { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(6)  };
DEFINE_MMIO_DEV(timer)          { BASE(0x00000000), ADDRWIDTH(1),  CSID(7)  };
DEFINE_MMIO_DEV(ata0)           { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(8)  };
DEFINE_MMIO_DEV(ata1)           { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(9)  };
DEFINE_MMIO_DEV(fdd)            { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(10) };
DEFINE_MMIO_DEV(pep0)           { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(11) };
DEFINE_MMIO_DEV(pep1)           { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(12) };
DEFINE_MMIO_DEV(pep2)           { BASE(0xFFFF0000), ADDRWIDTH(1),  CSID(13) };
DEFINE_MMIO_DEV(uart)           { BASE(0x00000000), ADDRWIDTH(1),  CSID(14) };
DEFINE_MMIO_DEV(kbms)           { BASE(0x00000000), ADDRWIDTH(1),  CSID(15) };
DEFINE_MMIO_DEV(eth)            { BASE(0x00000000), ADDRWIDTH(1),  CSID(16) };

#undef  DEFINE_MMIO_DEV
#undef  BASE
#undef  ADDRWIDTH
#undef  CSID

uint8_t assign_

#endif  // __MMIO_H__
