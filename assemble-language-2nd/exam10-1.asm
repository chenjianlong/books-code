assume cs:code

data segment
	db 'Welcome to masm!',0
data ends

code segment
start:
	mov dh,8
	mov dl,3
	mov cl,2
	mov ax,data
	mov ds,ax
	mov si,0
	call show_str

	mov ax,4c00h
	int 21h

; 功能：在指定位置，用指定颜色，显示一个用 0 结束的字符串
; 参数：(dh)=行号(0~24),(dl)=列号(0-79)
;       (cl)=颜色,ds:si 指向字符串的首地址
; 返回：无
show_str:
	push bx
	push dx

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
s:
	mov cl, [si]
	jcxz ok
	mov es:[bx],cl
	inc bx
	mov es:[bx],dh
	inc bx
	inc si
	jmp s

ok:
	pop dx
	pop bx
	ret

code ends

end start
