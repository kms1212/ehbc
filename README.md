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
  - Custom PCI-like expansion port (PEP, Peripheral Expansion Port)
  - 16-bit ISA bus
  - 8/16-bit PP Bus for low-speed peripherals
  - Floppy, IDE, RS232, UART, USB, Ethernet, Audio, etc.
- Advanced Memory Features
  - DRAM Controller with FPM and Read-Modify-Write support
  - 8-channel DMA support
- ... and so on

## Major ICs
- Main CPU MC68030 (@ 25, 33, 50MHz)
- Floating-point coprocessor MC68882 (@ 25, 33, 50MHz)
- One EPM7128SLC84 and two EPF10K130EQC240 implementing some critical features, as follows:
  - Programmable Interuupt Controller / Address Decoder
  - DRAM & 8-Channel DMA Controller with Cache
  - System Bus Bridge (Processor Local Bus, PEP, ISA, PP)
- ATMega32-16P working as System Master Controller
- RTL8019AS ethernet controller
- CS4231A audio codec
- SL811HS USB host controller
- MC68901 MFP (system timer, USART, and GPIO)
- VT82C42 keyboard and mouse controller
- PC8477BV floppy disk controller
- DS1307 RTC
- 25LC256 EEPROM
- Si5351A 3-channel clock generator
- PAC1932 power monitor
- EMC1701 power monitor with temperature sensor
- ADP5050 programmable DC-DC buck converter

## Documents
- https://www.figma.com/file/gA8tGpJNsGpitqZxiAOFYH/68k30-hbc-Functional-Block-Diagrams?type=design&node-id=6%3A522&mode=design&t=2HDdQic9h6DKRu98-1
- ./docs
