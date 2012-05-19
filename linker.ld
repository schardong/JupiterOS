/* Link.ld -- Linker script for the kernel - ensure everything goes in the */
/*            Correct place.  */
/*            Original file taken from Bran's Kernel Development */
/*            tutorials: http://www.osdever.net/bkerndev/index.php. */

OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
phys = 0x00100000;
SECTIONS
{
    . = phys;

    .__mbHeader : AT(ADDR(.__mbHeader)) {
      *(.__mbHeader)
    }

    .text ALIGN(4096) : AT(ADDR(.text)) {
        code = .; _code = .; __code = .;
        *(.text)
    }

    .data ALIGN(4096) : AT(ADDR(.data)){
        data = .; _data = .; __data = .;
        *(.data)
        *(.rodata)
    }

    .bss ALIGN(4096) : AT(ADDR(.bss)) {
        bss = .; _bss = .; __bss = .;
        *(.bss)
    }

    end = .; _end = .; __end = .;
}
