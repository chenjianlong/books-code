assume cs:code

data segment
	db 10 dup (0FFH)
data ends

code segment
start:
	mov ax,12666
	mov bx,data
	mov ds,bx
	mov si,0
	call dtoc

	mov dh,8
	mov dl,3
	mov cl,2
	call show_str
	mov ax,4c00h
	int 21h

; 功能：将 word 型数据转变为表示十进制数的字符串，字符串以 0 为结尾符
; 参数：(ax)=word 型数据
;		ds:si 指向字符串的首地址
; 返回：无
dtoc:
	push si
	push di
	push ax
	push cx
	push dx


s1:
	mov cx,10
	mov dx,0
	div cx

	add dx,30h
	push dx
	inc si

	mov cx,ax
	jcxz convert
	jmp s1

convert:
	; convert string
	mov [si],0
	mov cx,si
	mov si,0
doconv:
	pop ax
	mov [si],al
	inc si
	loop doconv

ok2:
	pop dx
	pop cx
	pop ax
	pop di
	pop si
	ret


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
