	;; File: start.asm
	;; Author: Guilherme Gonçalves Schardong.
	;; Entry point.
	;; File created on 24 June, 2011, 14:43

MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]
[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
[EXTERN code]                   ; Start of the '.text' section.
[EXTERN bss]                    ; Start of the .bss section.
[EXTERN end]                    ; End of the last loadable section.
mboot:
	dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each
                              ; 4-byte boundary in your kernel file
	dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
	dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct
  
	dd  mboot                   ; Location of this descriptor
	dd  code                    ; Start of kernel '.text' (code) section.
	dd  bss                     ; End of kernel '.data' section.
	dd  end                     ; End of kernel.
	dd  start                   ; Kernel entry point (initial EIP).

[GLOBAL start]                  ; Kernel entry point.
[EXTERN main]                   ; This is the entry point of our C code
start:
	push ebx		;Stores the multiboot header location to be used by the kernel.
	push esp		;Stores the stack address so that we can move it later.
	cli
	call main
	jmp $
