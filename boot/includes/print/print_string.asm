; Prints text on BX register
print_string:           ; prints value on bx
    pusha
    mov ah, 0x0e        ; tele-type mode

    print_loop:
        mov ch, [bx]        ; copy value to 8 bit register
        cmp ch, 0           ; if we reach end of string
        je print_loop_end   ; then break and return
        
        mov al, ch          ; move char to al to then print
        int 0x10            ; call interrupt
        add bx, 1           ; move to next char in string
        jmp print_loop      ; continue


    print_loop_end:
    popa
    ret
