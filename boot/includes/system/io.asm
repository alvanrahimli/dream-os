import_in:
    mov edx, [esp + 4]
    in al, dx
    ret

import_out:
    mov edx, [esp + 4]
    mov eax, [esp + 8]
    out dx, al
    ret