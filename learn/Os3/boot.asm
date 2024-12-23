org 0x00 
bits 16 
section code 
.init:
	mov eax,0xb800
	mov es,eax 
	xor eax,eax
.clear:
	mov byte[es:eax],0
	inc eax
	mov byte[es:eax],0x30
	cmp eax,2*25*80
	jl .clear
.main:
	mov byte [es:0x00],"H"
	mov byte [es:0x01],0x30 
	mov byte [es:0x02],0x30 

jmp $
times 510-($-$$) db 0 
db 0x55
db 0xaa
