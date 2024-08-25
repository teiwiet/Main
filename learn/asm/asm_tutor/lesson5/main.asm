%include 'functions.asm'

section .data
msg db "Hello World",0xa,0 
msg1 db "Hello World no.2",0xa,0
section .text
global _start
_start:
	mov eax,msg 
	call print
	 
	mov eax,msg1
	call print

	call exit
