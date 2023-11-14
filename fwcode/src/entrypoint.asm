;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Firmware Entry Point
; Performs:
; - Processor Initialization
; - CDC Initialization
; - Memory Test
; - Stack Initialization
; - Timer and USART Initialization
; - Segment Preperation
;
    include "asm/constants.inc"
    include "asm/ldsymbols.inc"
    include "asm/cmain.inc"
    include "asm/cdc.inc"
    include "asm/smc.inc"
    include "asm/mfp.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    org $00000000
    section .vector

_asm_vector::
    dc.l $00000000
    dc.l _start
    dc.l _bus_address_error
    dc.l _bus_address_error
    dcb.l 252


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    section .text

_start::
    ; The very first code after the reset interrupt
    ; %d0=0x00000000 %d1=0x00000000 %d2=0x00000000 %d3=0x00000000
    ; %d4=0x00000000 %d5=0x00000000 %d6=0x00000000 %d7=0x00000000
    ; 
    ; %a0=0x00000000 %a1=0x00000000 %a2=0x00000000 %a3=0x00000000
    ; %a4=0x00000000 %a5=0x00000000 %a6=0x00000000 %sp=0x00000000
    ; 
    ; %sr:     T<1:0>=00 S=1 M=0 I<2:0>=0b111 X=0 N=0 Z=0 V=0 C=0
    ; 
    ; %pc=0x00000400 %vbr=0x00000000 %cacr=0x00000000
    ; 

    ; It is able to access the OPB devices before the configuration of the SBC.
    ; So you can access to the SMC to indicate errors occured before the proper
    ; configuration of the SBC.

    ; CPU Reset Acknowledgent
    move.b #SMC_C_RSTACK,SMC_CMDR

_processor_init:
    nop

_cdc_init:
    ; This code temporarily initializes the CDC.
    ; You can use only 128kiB of DRAM without caching currently.

    ; Module Count: 1, AMUX Type: 3, Bank Size: 128k, Single-sided, FPM
    move.l #V_CDC_MICR,CDC_MICR

    ; tRAC: 5 Clock Cycles (100ns @ 50MHz)
    ; Refresh: 375000 Cycles (15ms @ 25MHz)
    move.l #V_CDC_MMTR,CDC_MMTR

    ; Memory Map Options:
    ; Enable Flash, Enable DRAM, Enable DRAM relocation
    move.b #V_CDC_MMOR,CDC_MMOR

    ; Cache Memory Options:
    ; Inhibit L1 Cache, Disable L2 Cache, Write-back Mode
    move.b #V_CDC_CMOR,CDC_CMOR

_memtest:
    ; DRAM Test
    move.l #$00100000,a0

.wloop:
    ; Write data to address
    move.l a0,(a0)
    cmp.l #$00120000,a0
    beq .wloop_exit
    add.l #$100,a0
    jmp .wloop

.wloop_exit:
    move.l #$00100000,a0

.rloop:
    ; Read and erase data
    cmp.l (a0),a0
    bne .error
    move.l #0,(a0)
    add.l #$100,a0
    cmp.l #$00120000,a0
    beq .success
    jmp .rloop

.error:
    ; Memory not present. Beep 2 times shortly.
    move.b #SMC_C_BEEP2,SMC_CMDR
    jmp *

.success:

_stack_init:
    ; Set stack pointer to the end of the DRAM space
    move.l #$00120000,sp

_timer_init:
    ; MFP operates at 3.6864MHz clock
    ; 9600hz clock configuration in the channel D for the USART
    ; : /16 prescaler, delay count 24
    move.b #24,MFP_TDDR
    move.b #$03,MFP_TCDCR

_usart_init:
    ; baud 8-N-1 configuration, Transmission only
    move.b #%0000100,MFP_UCR
    move.b #%0000000,MFP_RSR
    move.b #%0000011,MFP_TSR

_data_copy:
    ; Copy initial values of section .data to DRAM space
    move.l #__data_init,a0   ; Copy source
    move.l #__data_start,a1  ; Copy destination

.loop:
    move.l (a0)+,(a1)+
    cmp.l #__data_end,a1
    bne .loop

_set_cvector:
    xref c_vector
    move.l #c_vector,d0
    movec d0,vbr

_jump:
    ; Jump to C
    jsr _cmain
    jmp *

_reset:
    reset

_bus_address_error:
    ; Bus or address error. Beep 3 times shortly.
    move.b #SMC_C_BEEP2,SMC_CMDR
    jmp *
