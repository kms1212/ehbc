; SMC Registers
SMC_SR      equ $FF010000  ; 8b
SMC_CMDR    equ $FF010000  ; 8b

; SMC Command Codes
SMC_C_BEEP1     equ $E0
SMC_C_BEEP2     equ $E1
SMC_C_BEEP3     equ $E2
SMC_C_BEEP4     equ $E3
SMC_C_LBEEP2    equ $E4
SMC_C_LBEEP3    equ $E5
SMC_C_LBEEP4    equ $E6
SMC_C_LBEEP5    equ $E7

SMC_C_SYSHALT   equ $F0
SMC_C_RSTACK    equ $FF
