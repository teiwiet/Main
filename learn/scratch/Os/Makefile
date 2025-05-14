qemu=qemu-system-x86_64 
all:
	nasm boot/boot.asm -f bin -o boot/bin/boot.bin
	nasm boot/kernel_entry.asm -f elf -o boot/bin/kernel_entry.bin
	gcc boot/main.c -c -m32 -ffreestanding -o boot/bin/kernel.o 
	ld -m elf_i386 -Ttext 0x1000 boot/bin/kernel.o boot/bin/kernel_entry.bin -o boot/bin/kernel.img 
	objcopy -O binary -j .text boot/bin/kernel.img boot/bin/kernel.bin 
	cat boot/bin/boot.bin boot/bin/kernel.bin > os.img 
clean:
	rm boot/bin/*
run:
	$(qemu) -drive format=raw,file=os.img
