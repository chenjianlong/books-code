assume cs:code

a segment
	db 1,2,3,4,5,6,7,8
a ends

b segment
	db 1,2,3,4,5,6,7,8
b ends

c1 segment
	db 0,0,0,0,0,0,0,0
c1 ends

code segment
start:
	mov ax,a
	mov ds,ax

	mov ax,b
	mov es,ax

	mov ax,c1
	mov ss,ax

	mov sp,8

	mov bx,7
	mov cx,4
s:
	mov ah,[bx]
	add ah,es:[bx]
	dec bx
	mov al,[bx]
	add al,es:[bx]
	push ax
	dec bx
	loop s

	mov ax,4c00h
	int 21h
code ends

end start
