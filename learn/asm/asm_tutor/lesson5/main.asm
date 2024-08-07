%include "functions.asm" 
section .data
msg1 db "Hello, brave new world",0xA 
msg2 db "This is how we recycle in nasm",0xA 

section .text 
global _start
_start:
	mov eax,msg1 
	call print

	mov eax,msg2
	call print 

	call quit ; exit func
