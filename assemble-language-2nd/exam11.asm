assume cs:codesg

datasg segment
	db "Beginner's All-purpose Symbolic Instruction Code.",0
datasg ends

codesg segment
begin:
	mov ax, datasg
	mov ds, ax
	mov si, 0
	call letterc

	mov ax, 4c00h
	int 21h

letterc:
	push si
	push ax

letterc_0:
	mov al, [si]
	cmp al, 0
	jz letterc_end
	cmp al, 'a'
	jb letterc_next
	cmp al, 'z'
	ja letterc_next
	and al,11011111b
	mov [si], al

letterc_next:
	inc si
	jmp letterc_0

letterc_end:
	pop ax
	pop si
	ret

codesg ends

end begin
