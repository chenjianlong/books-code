assume cs:code

code segment
start:
	mov ax,70h
	shl ax,1

	mov bx,70h
	mov cl,3
	shl bx,cl
	add ax,bx

	mov ax,4c00h
	int 21h
code ends
end start
