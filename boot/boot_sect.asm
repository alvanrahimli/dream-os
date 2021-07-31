[org 0x7c00]
KERNEL_OFFSET equ 0x1000        ; Where we will load kernel

    mov [BOOT_DRIVE], dl        ; BIOS stores boot drive in dl register
                                ; save it.
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE       ; Print read mode message
    call print_string

    call load_kernel

    call switch_to_pm

    jmp $

; Include routines
%include "print/print_string.asm"
%include "print/print_string_pm.asm"
%include "system/gdt.asm"
%include "system/switch_to_pm.asm"
%include "disk/disk_load.asm"
%include "hex/print_hex.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET       ; Setting up parameters for disk_load routine
    mov dh, 15                  ; Please read 15 sectors
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET          ; Call kernel executable starting point
    jmp $


; Global variables
BOOT_DRIVE: db 0
MSG_REAL_MODE: db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE: db "Successfully landed on 32-bit protected mode!", 0
MSG_LOAD_KERNEL: db "Loading kernel into memory", 0

; Boot sector padding
times 510-($-$$) db 0
dw 0xaa55