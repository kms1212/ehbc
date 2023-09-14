#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "types.h"
#include "utils.h"

// Memory Map Definitions

#define MMAP_FIRMWARE_START     
#define MMAP_FIRMWARE_END       
#define MMAP_FIRMWARE_SIZE      

#define MMAP_FWSRAM_START       
#define MMAP_FWSRAM_END         
#define MMAP_FWSRAM_SIZE        

#define MMAP_DRAM_START         
#define MMAP_DRAM_END           
#define MMAP_DRAM_SIZE          

#define MMAP_MMIO_START         
#define MMAP_MMIO_END           
#define MMAP_MMIO_SIZE          


ptr_t memcpy(ptr_t dest, const ptr_t src, size_t sz);

#endif  // __MEMORY_H__
