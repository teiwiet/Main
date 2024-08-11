.data ; data area 
sum DWORD 0
.code ; code area
main PROC 
	mov eax,5
	add eax,5
	mov sum,eax 
	INVOKE ExitProcess,0 ;end the programm
