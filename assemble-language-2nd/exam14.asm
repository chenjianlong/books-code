assume cs:code

data segment
	db 'yy/mm/dd hh:MM:ss','$'
	db 9,8,7,4,2,0
data ends

code segment
start:
	mov ax,data
	mov ds,ax
	mov si,18
	mov di,0
	mov cx,6
s:
	push cx

	mov al,[si]
	inc si
	out 70h,al
	in al,71h

	mov ah,al
	mov cl,4
	shr ah,cl
	and al,00001111b

	add ah,30h
	add al,30h

	mov [di],ah
	inc di
	mov [di],al
	add di,2

	pop cx
	loop s

	mov ah,2
	mov bh,0
	mov dh,8
	mov dl,12
	int 10h

	mov dx,0
	mov ah,9
	int 21h

	mov ax,4c00h
	int 21h
code ends
end start
