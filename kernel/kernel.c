#include "../drivers/screen/includes/screen.h"
#include "../drivers/screen/includes/text.h"
#include "../lib/string/includes/string.h"
#include "../cpu/includes/isr.h"

void main() {
    clrscr();

    idt_install();

    println("The OS");
    println("Welcome, friend. Kernel successfully loaded to memory");
}
