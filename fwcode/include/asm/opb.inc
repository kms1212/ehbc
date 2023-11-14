; MMIO Base Address for OPB Devices: 0xFF010000
; Address Map of OPB Devices
; 0xFF0100?? (CS00): SMC
; 0xFF0101?? (CS01): MFP (RS232 / Timer / Interrupt)
; 0xFF0104?? (CS04): SPI Controller
; 0xFF0105?? (CS05): I2C Controller
; 0xFF0106?? (CS06): USB Controller
; 0xFF0107?? (CS07): 8242 KB/MS Controller
; 0xFF0108?? (CS08): FDD Controller
; 0xFF010C?? (CS12): Audio CODEC
; * Reserved address spaces are omitted.
; * "?" is a placeholder of a hexadecimal value.

; OPB Devices
OPB_SMC     equ $FF010000
OPB_MFP     equ $FF010100
OPB_SPI     equ $FF010400
OPB_I2C     equ $FF010500
OPB_USB     equ $FF010600
OPB_8242    equ $FF010700
OPB_FDC     equ $FF010800
OPB_ACODEC  equ $FF010C00
