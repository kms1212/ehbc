#ifndef __SMC_H__
#define __SMC_H__

#include "types.h"

#define MMAP_DEFAULT_MMIO_SMC_CMDADDR   
#define MMAP_DEFAULT_MMIO_SMC_DATAADDR  

#define SMC_CMD_READ_MMPRES             
#define SMC_CMD_READ_HEADERCFG          
#define SMC_CMD_READ_PEPPRES            
#define SMC_CMD_READ_SWITCH             
#define SMC_CMD_READ_FREQ               
#define SMC_CMD_READ_RTC                
#define SMC_CMD_READ_EEPROM             

#define SMC_CMD_WRITE_FREQ              
#define SMC_CMD_WRITE_RTC               
#define SMC_CMD_WRITE_EEPROM            

#define SMC_CMD_I2C_DIRECTWRITE         
#define SMC_CMD_I2C_DIRECTREAD          

#define SMC_CMD_ADDEC_WRITE             
#define SMC_CMD_ADDEC_READ              

#define SMC_CMD_SYSRESET                
#define SMC_CMD_SYSPWDN                 



#endif  // __SMC_H__
