org 0x7c00 
bits 16 

_start:
	jmp short start 
	nop 

times 33 db 0 

start:
	cli 
	; enable a20 line
	in al,0x92 
	or al,2
	out 0x92,al
	; load gdt 
	lgdt [gdt_descriptor]
	mov eax,cr0 
	or eax,0x1 
	mov cr0,eax 

	jmp code_seg:protected_start

[bits 32]
protected_start:
	mov ax,data_seg 
	mov ss,ax 
	mov ds,ax 
	mov es,ax 
	mov fs,ax 
	mov gs,ax 

	mov ebp,0x90000 
	mov esp,ebp 
	
	jmp $
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
code_seg equ gdt_code - gdt_start 
data_seg equ gdt_data - gdt_start 
times 510-($-$$) db 0
dw 0xaa55
