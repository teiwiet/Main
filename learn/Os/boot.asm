ORG 0x7c00
BITS 16
CODE_SEG equ gdt_code - gdt_start 
DATA_SEG equ gdt_data - gdt_start 

_start:
	jmp short start 
	nop

times 33 db 0 

start:
	jmp 0:step2 
step2:
	cli
	mov ax,0
	mov ds,ax 
	mov es,ax
	mov ss,ax
	mov sp,0x7c00 
	sti 

	jmp $

load_protected:
	cli 
	lgdt[gdt_descriptor]
	mov eax,cr0
	or eax,0x1 
	mov cr0,eax 
	jmp CODE_SEG:load32

; https://wiki.osdev.org/Global_Descriptor_Table
;gdt section 
gdt_start:
gdt_null:
	dd 0x0 
	dd 0x0 
;offset 0x8 
gdt_code:		; address for the cs point to
	dw 0xffff 	; limit first 0-15 bits 
	dw 0 		; base first 0-15 bits
	db 0 		; base 16-23 bits
	db 0x9a		; access byte with default value
	db 11001111b 	; high 4 bits flag and the low 4 bit flags
	db 0
;offset 0x10
gdt_data: 		; ds,ss,es,fs,gs
	dw 0xffff 	; limit first 0-15 bits
	dw 0 		; base first 0-15 bits 
	db 0 		; base 16-23 bits
	db 0x92		; access byte for data section 
	db 11001111b	; high 4 bits flag and the low 4 bit flags
	db 0
gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start
[BITS 32]
load32:
	jmp $
times 510-($-$$) db 0 
dw 0xaa55


