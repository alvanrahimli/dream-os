C_SOURCES = $(wildcard kernel/*.c drivers/screen/*.c lib/*/*.c)

OBJ = ${C_SOURCES:.c=.o}

all: os-image

run: all
	qemu-system-i386 os-image

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image


kernel.bin: kernel/kernel_entry.o cpu/idt.o boot/includes/system/idt.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ -m elf_i386 --oformat binary

%.o: %.c
	gcc -ffreestanding -m32 -fno-pie -c $< -o $@

%.o: %.asm
	nasm $< -f elf -I boot/includes -o $@

%.bin: %.asm
	nasm $< -f bin -I boot/includes -o $@

clean:
	rm -rf bin/*.bin bin/*.dis bin/*.o os-image
	rm -rf kernel/*.o boot/*.bin drivers/*.o drivers/screen/*.o lib/*/*.o boot/*/*/*.o
	rm -f os-image