# MC68030 Expandable Homebrew Computer

## Milestones

## EHBC Motherboard (/kicad)
### Main Goals
- A rich-function homebrew computer with completely extensible specification
- ATX-dimension compatible motherboard
- Configurable firmware
- Dual-boot function with Linux and custom multitasking OS
- Four 72-pin SIMM DRAM slots
- Rich peripheral interconnection features
  - MMIO with custom address configuration
  - Custom PCI-like expansion port (PEP, Peripheral Expansion Port)
  - 16-bit ISA bus
  - 8/16-bit PP Bus for low-speed peripherals
  - Floppy, IDE, RS232, UART, USB, Ethernet, Audio, etc.
- Advanced Memory Features
  - DRAM Controller with FPM and Read-Modify-Write support
  - 8-channel DMA support
- TBD

### Major ICs
- Main CPU MC68030 (@ 25, 33, 50MHz)
- Floating-point coprocessor MC68882 (@ 25, 33, 50MHz)
- Two EPF6016QC240 implementing some important features, as follows:
  - DRAM & 8-Channel DMA Controller with Cache
  - System Bus Controller (Processor Local Bus, PEP, ISA, OPB, ATA)
- ATMega32-16P working as a System Master Controller
- RTL8019AS ethernet controller
- CS4231A audio codec
- SL811HS USB host controller
- MC68901 MFP (system timer, USART, and GPIO or interrupt)
- VT82C42 keyboard and mouse controller
- PC8477BV floppy disk controller
- DS1307 RTC
- 25LC256 EEPROM
- PAC1932 power monitor
- EMC1701 power monitor with temperature sensor
- ADP5050 programmable DC-DC buck converter
- MX8315 configurable clock generator
- Auxillary ICS551, 542, and 501s for clock generation
- TBD

## PEP Graphics Controller Expansion Card (/kicad)
- CL-GD5436 VGA GUI accelerator

## 

## Documents
- https://www.figma.com/file/gA8tGpJNsGpitqZxiAOFYH/68k30-hbc-Functional-Block-Diagrams?type=design&node-id=6%3A522&mode=design&t=2HDdQic9h6DKRu98-1
- ./docs
