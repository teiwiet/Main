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

	jmp code_seg:load32

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
	mov eax,1 
	mov ecx,100 
	mov edi,0x0100000
	call ata_lba_read 
	
	jmp code_seg:0x0100000 

ata_lba_read:
	mov ebx,eax 
	; send the highest 8 bits of the lba to the hard disk controller 
	shr eax,24 
	or eax,0xE0
	mov dx,0x1F6
	out dx,al 
	; finished sending the highest 8 bits of the lba 
	
	;send the total sectors to read 
	mov eax,ecx 
	mov dx,0x1F2 
	out dx,al 
	;finished sending the total sectors to read 

	mov eax,ebx
	mov dx,0x1F3 
	out dx,al 
	; finished sending more bits of the lba 
	
	; send more bits of the lba 
	mov dx,0x1F4 
	mov eax,ebx 
	shr eax,8 
	out dx,al 
	; finished sending more bits of the lba 


	; send upper 16 bits of the lba 
	mov dx,0x1F5 
	mov eax,ebx
	shr eax,16 
	out dx,al 

	mov dx,0x1F7 
	mov al,0x20 
	out dx,al


.next_sector:
	push ecx 

.try_again:
	mov dx,0x1f7 
	in al,dx 
	test al,8 
	jz .try_again

; we need to read 256 words at a time 
	mov ecx,256
	mov dx,0x1f0 
	rep insw 
	pop ecx 
	loop .next_sector

	; end of reading sectors into memory 
	ret 

code_seg equ gdt_code - gdt_start 
data_seg equ gdt_data - gdt_start 
times 510-($-$$) db 0
dw 0xaa55
