[bits 16]
[org 0x7c00]

_start:
	jmp short start 
	nop  

times 33 db 0 
start:
	cli							; clear the interrupt 
	lgdt[gdt_descriptor]
	mov eax,cr0 
	


times 510-($-$$) db 0 
dw 0xaa55 
