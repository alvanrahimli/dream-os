#include "includes/idt.h"
#include "../kernel/includes/util.h"
#include "../drivers/screen/includes/text.h"
#include "../lib/types.h"

idt_entry_t idt[256];
idt_ptr_t idtp;

char* exception_messages[] = {
    "Division by zero",
    "Debug",
    // ...
    "Reserved"
};

extern void idt_load();

void idt_set_gate(unsigned char num, unsigned long base,
                  unsigned short sel, unsigned char flags)
{
   idt[num].base_hi = *((unsigned short*)&base);
   idt[num].base_lo = *((unsigned short*)((&base) + 1));
   idt[num].sel = sel;
   /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
   idt[num].flags = flags;
   idt[num].always0 = 0;
}

void idt_install() {
    print("INF :: Installing IDT... ");
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;
    /* Clear out the entire IDT, initializing it to zeros */
    memset((char*)&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */
    


    /* Points the processor's internal register to the new IDT */
    idt_load();
    println("Done");
}
