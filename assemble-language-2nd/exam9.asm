assume cs:code,ds:data,ss:stack

data segment
	db 'welcome to masm!'
data ends

stack segment
	db 16 dup (0)
stack ends

code segment
start:
	mov ax,0b800h
	mov ds,ax

	mov ax,stack
	mov ss,ax
	mov sp,16

	mov ax,data
	mov es,ax


	mov di,0
	mov cx,3

	mov dh,01110001b ; push text attribute
	push dx
	mov dh,00100100b
	push dx
	mov dh,00000010b
	push dx
s:
	pop dx
	push cx
	push di
	mov cx,16
	mov si,0
s0:
	mov dl, es:[si]
	mov 1824[di],dx
	inc si
	add di,2
	loop s0

	pop di
	pop cx
	add di,160
	loop s

	mov ax,4c00h
	int 21h
code ends

end start
