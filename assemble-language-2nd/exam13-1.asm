assume cs:code

data segment
	db 'Welcome to masm!',0
data ends

code segment
start:
	mov ax,cs
	mov ds,ax
	mov si,offset show_str
	mov ax,0
	mov es,ax
	mov di,200h
	mov cx,offset show_str_e-offset show_str
	cld
	rep movsb

	mov ax,0
	mov es,ax
	mov word ptr es:[7ch*4],200h
	mov word ptr es:[7ch*4+2],0

	mov ax,4c00h
	int 21h

; 功能：在指定位置，用指定颜色，显示一个用 0 结束的字符串
; 参数：(dh)=行号(0~24),(dl)=列号(0-79)
;       (cl)=颜色,ds:si 指向字符串的首地址
; 返回：无
show_str:
	push bx
	push dx
	push es

	mov bx,0b800h
	mov es,bx
	mov bx,0
	mov al,160
	mul dh
	add bx,ax
	mov al, 2
	mul dl
	add bx,ax

	mov dh,cl
	mov cx,0
show_str_l:
	mov cl, [si]
	jcxz show_str_ok
	mov es:[bx],cl
	inc bx
	mov es:[bx],dh
	inc bx
	inc si
	jmp show_str_l

show_str_ok:
	pop es
	pop dx
	pop bx
	iret
show_str_e:
	nop

code ends

end start
