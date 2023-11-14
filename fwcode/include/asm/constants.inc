; Module Count: 1, AMUX Type: 3, Bank Size: 128k, Single-sided, FPM
V_CDC_MICR      equ $31000000

; tRAC: 5 Clock Cycles (100ns @ 50MHz)
; Refresh: 375000 Cycles (15ms @ 25MHz)
V_CDC_MMTR      equ $5005B8D8

; Memory Map Options:
; Enable Flash, Enable DRAM, Enable DRAM relocation
V_CDC_MMOR      equ %01110000

; Cache Memory Options:
; Inhibit L1 Cache, Disable L2 Cache, Write-back Mode
V_CDC_CMOR      equ %00000000
