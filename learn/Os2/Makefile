all:
	nasm -f bin boot.asm -o boot.bin
	dd if=boot.bin of=boot.img bs=512 count=1 conv=notrunc
clean:
	rm boot.bin
