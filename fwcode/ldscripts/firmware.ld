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
    .exception_vector : {
        . = ALIGN(4);
        __exception_vector_start = .;

        KEEP(*(.vector));

        __exception_vector_end = .;
    } >FLASH

    .text : {
        . = ALIGN(4);
        __text_start = .;

        *(.text .text.*)

        __text_end = .;
    } >FLASH 

    .rodata : {
        . = ALIGN(4);
        __rodata_start = .;

        *(.rodata .rodata.*)

        __text_end = .;
    }

    .data : {
        __data_init = LOADADDR(.data);
        . = ALIGN(4);
        __data_start = .;

        *(.data .data.*)

        __data_end = .;
    } >RAM AT >FLASH

    .fill : {
        FILL(0xFF);
        . = ORIGIN(FLASH) + LENGTH(FLASH);
    } AT >FLASH

    .bss(NOLOAD) : {
        . = ALIGN(4);
        __bss_start = .;

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
