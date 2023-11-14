OUTPUT_FORMAT(elf32-m68k)

MEMORY {
    /* Bottom of the address space */
    FLASH(rx)   : ORIGIN = 0x00000000, LENGTH = 1M

    /* 1MiB above from the bottom */
    RAM(rwx)    : ORIGIN = 0x00100000, LENGTH = 4079M

    /* Last 16MiB of the address space */
    MMIO(rw)    : ORIGIN = 0xFF000000, LENGTH = 16M
}

SECTIONS {
    .vector : {
        . = ALIGN(4);
        KEEP(*(.vector));
    } >FLASH

    .text : {
        __text_start = .;

        *(.text .text.*)
        *(.rodata .rodata.*)

        __text_end = .;
    } >FLASH 

    .data : {
        __data_init = LOADADDR(.data);
        __data_start = .;

        . = ALIGN(4);
        *(.data .data.*)
        . = ALIGN(4);

        __data_end = .;
    } >RAM AT >FLASH

    .fill : {
        FILL(0xFF);
        . = ORIGIN(FLASH) + LENGTH(FLASH);
    } AT >FLASH

    .bss(NOLOAD) : {
        __bss_start = .;

        . = ALIGN(4);
        *(.bss .bss.*)
        *(COMMON)

        __bss_end = .;
    } >RAM

    .noinit(NOLOAD) : {
        __noinit_start = .;

        . = ALIGN(4);
        *(.noinit .noinit.*)

        __noinit_end = .;
    } >RAM

    .mmio(NOLOAD) : {
        __mmio_start = .;
    } >MMIO
}
