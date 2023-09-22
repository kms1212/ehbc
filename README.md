# 68k30-hbc
MC68030 Expandable Homebrew Computer

## Main Goals
- A rich-function homebrew computer with completely extensible specification
- ATX-dimension compatible motherboard
- Configurable firmware
- Dual-boot function with Linux and custom multitasking OS
- Four 72-pin SIMM DRAM slots
- Rich peripheral interconnection features
  - MMIO with custom address configuration
  - Custom memory-mapped expansion port (PEP, Peripheral Expansion Port)
  - 16-bit EISA bus
  - Floppy, IDE, RS232, UART, USB, Ethernet, Audio, etc.
- Advanced Memory Features
  - DRAM Controller with FPM and Read-Modify-Write support
  - 2+4-channel DMA support
- ... and so on

## Major ICs
- Main CPU MC68030 (@ any clock speed)
- Floating-point coprocessor MC68882 (@ any clock speed)
- 3 EPM7128SLC84 implementing some critical features, as follows:
  - Configurable Address Decoder
  - Programmable Interrupt Controller / Bus Signaling Format Converter
  - DRAM Controller
- ATMega32-16P working as System Master Controller
- RTL8019AS ethernet controller
- MC68440 and MC68450 DMA controller (up to 6 DMA channels)
- CS4231A audio codec
- SL811HS USB host controller
- MC68681 DUART (channel A for RS232, channel B for TTL)
- MC68901 MFP (system timer and GPIO)
- VT82C42 keyboard and mouse controller
- PC8477BV floppy disk controller
- DS1307 RTC
- 25LC256 EEPROM
- Si5351A 3-channel clock generator

## Documents
- https://www.figma.com/file/gA8tGpJNsGpitqZxiAOFYH/68k30-hbc-Functional-Block-Diagrams?type=design&node-id=6%3A522&mode=design&t=2HDdQic9h6DKRu98-1
- ./docs
