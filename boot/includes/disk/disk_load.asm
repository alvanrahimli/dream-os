; Loads DH sectors to ES:BX from drive DL
disk_load:
    push dx             ; Store DX on stack so later we can recall
                        ; how many sectors were requested to read
                        ; even if it is altered in the meantime
    mov ah, 0x02        ; BIOS read sector function
    mov al, dh          ; Read DH sectors (dh & al => requested sector count)
    mov ch, 0x00        ; Select cylinder 0 (ch => cylinder number)
    mov dh, 0x00        ; Select head 0
    mov cl, 0x02        ; Start reading from second sector 
                        ; (after the boot sector)

    int 0x13            ; BIOS interrupt for reading disk

    jc disk_error       ; Jump if carry flag (CF) is set
    pop dx              ; Restore DX from stack
    cmp dh, al          ; If AL (sectors read) != DH (sectors expected)

    jne disk_error      ; display disk_error message
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    xor bh, bh
    mov bl, ah
    call print_hex
    jmp $

DISK_ERROR_MSG: db "ERR :: DISK :: READ :: ", 0
