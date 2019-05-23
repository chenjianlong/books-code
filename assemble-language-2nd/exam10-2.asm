assume cs:code,ss:stack

stack segment
	dw 16 dup (0)
stack ends

code segment
start:
	mov ax,stack
	mov ss,ax
	mov sp,32

	mov dx,99
	mov ax,1000h
	mov cx,2
	call divdw
	mov ax,4c00h
	int 21h

; 进行不会溢出的除法运算
; 参数：被除数：dx:ax，除数：cx
; 返回：商：dx:ax，余数：cx
divdw:
	push bx
	push si

	mov bx,ax

	mov ax,dx
	mov dx,0
	div cx
	mov si,ax
	mov ax,bx
	div cx
	mov cx,dx
	mov dx,si

	pop si
	pop bx
	ret
code ends

end start
