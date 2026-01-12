qemu=qemu-system-x86_64 


all:
	nasm -f bin src/boot/boot.asm -o boot.bin

run:
	$(qemu) -hda boot.bin
