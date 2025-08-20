[bits 16]
[org 0x7c00]
switch:
	mov ax,0x4f01 
	mov cx,0x111
	mov bx,0x800 
	mov es,bx 
	mov di,0x0
	int 0x10 

	register*16 + offset
	mov ax,0x4f02 
	mov bx,0x111
	int 0x10

	xor ax,ax 
	mov es,ax 
	mov ds,ax 

	mov ah,0x2 
	mov al,21
	mov ch,0x0 
	mov cl,0x2

	cli 
	lgdt[gdt_descriptor]

	mov eax,cr0
	or eax,0x1 
	mov cr0,eax 

	jmp code_seg:protected_start 

[bits 32]
	mov ax,data_seg 
	mov ss,ax 
	mov es,ax 
	mov fs,ax 
	mov gs,ax 
	mov ds,ax 

	mov ebp,0x90000 
	mov esp,ebp 
	
	jmp $
gdt_begin:
gdt_null:
	dd 0x00 
	dd 0x00 
gdt_code_seg:
	dw 0xffff 
	dw 0x00 
	db 0x00 
	db 10011010b 
	db 11001111b
	db 0x00 
gdt_data_seg:
	dw 0xffff 
	dw 0x00 
	db 0x00 
	db 10010010b 
	db 11001111b
	db 0x00 
gdt_end:
gdt_descriptor:
	dw gdt_end - gdt_begin - 1 
	dd gdt_begin 
code_seg equ gdt_code_seg - gdt_begin 
data_seg equ gdt_data_seg - gdt_begin 
times 510-($-$$) db 0 
dw 0xaa55
