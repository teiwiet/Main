[bits 16]
[org 0x7c00]

swtich:
	cli 
	lgdt[gdt_descriptor]
	mov eax,cr0 
	or eax,1 
	mov cr0,eax

