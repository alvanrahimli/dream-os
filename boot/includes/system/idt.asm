%include "print/print_string_pm.asm"

global idt_load:
extern idtp
idt_load:
    lidt [idtp]
    ; mov ebx, MSG_IDT_LOAD
    ; call print_string_pm
    ret

MSG_IDT_LOAD: db "IDT is being loaded"