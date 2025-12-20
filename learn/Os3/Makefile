qemu=qemu-system-x86_64
all:
	nasm -f bin ./src/boot/boot.asm -o bin/boot.bin 
clean:
	rm -rf bin/* 
run:
	$(qemu) -hda bin/boot.bin
