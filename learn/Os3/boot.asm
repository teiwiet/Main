[BITS 16]
[ORG 0x7c00]
start:
	mov ah,0xe
	mov al,"h"
	mov bx,0
	int 0x10
	jmp $
times 510-($-$$) db 0 
dw 0xaa55
