[bits 16]
; Switch to protected mode
switch_to_pm:
    cli                     ; Switch of interrupts (they won't work in PM either)
    
    lgdt [gdt_desciptor]    ; Load GDT Descriptor

    mov eax, cr0            ; To do actual switch to Proteced Mode,
    or eax, 0x1             ; we set first bit of cr0 (a control register)
    mov cr0, eax            ; Update the control register

    jmp CODE_SEG:init_pm


[bits 32]
init_pm:
    mov ax, DATA_SEG        ; Now in PM our old segments are meaningless,
    mov ds, ax              ; so we point our segment registers to the
    mov ss, ax              ; data seleector we defined in our GDT
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000        ; Update our stack position so it is right
    mov esp, ebp            ; at the top of the free space

    call BEGIN_PM