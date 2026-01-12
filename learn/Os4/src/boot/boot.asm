[bits 16]
[org 0x7c00]
_start:
	jmp short start 
	nop 

times 33 db 0 

start:
	cli 
	in al,0x92 
	or al,2
	out 0x92,al 

	mov eax,cr0 
	or eax,1 
	mov cr0,eax 
	lgdt[gdt_descriptor]
	jmp code_seg:load32 
	sti 

gdt_start:
gdt_null:
	dd 0x00 
	dd 0x00 
gdt_code:
	dw 0xffff 
	dw 0x0000 
	db 0x00 
	db 10011010b
	db 11001111b 
	db 0x00
gdt_data:
	dw 0xffff 
	dw 0x0000 
	db 0x00 
	db 10010010b
	db 11001111b 
	db 0x00
gdt_end:


gdt_descriptor:
	dw gdt_end - gdt_start - 1 
	dd gdt_start 

[bits 32]
load32:
	mov ax,data_seg 
	mov es,ax 
	mov ss,ax 
	mov gs,ax 
	mov fs,ax 
	mov fs,ax 

	mov ebp,0x00200000
	mov esp,ebp

	jmp $
code_seg equ gdt_code - gdt_start 
data_seg equ gdt_data - gdt_start 

times 510-($-$$) db 0 
dw 0xaa55
