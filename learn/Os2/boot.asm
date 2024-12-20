[BITS 16]
[ORG 0x7c00]

start:
	xor ax,ax
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov cs,ax 
	mov sp,0x7c00 
TestDiskExtension:
	mov [DriveId],dl
	mov ah,0x41
	mov bx,0x55aa
	int 0x13
	jc NotSupport
	cmp bx,0xaa55
	jne NotSupport
PrintMessage:
	mov ah,0x13
	mov al,1
	mov bx,0x1
	xor dx,dx
	mov bp,Message 
	mov cx,MessageLen 
	int 0x10
NotSupport:
End:
	hlt
	jmp End
DriveId: db 0 

Message: db "Disk extension is supported"
MessageLen: equ $ - Message
	; times (0x1be - ($-$$)) db 0 
	; db 80h
	; db 0,2,0
	; db 0f0h
	; db 0ffh,0ffh,0ffh
	; dd 1 
	; dd (20*16*63-1)
	; times (16*3) db 0
	times 510-($-$$) db 0
	dw 0xaa55
