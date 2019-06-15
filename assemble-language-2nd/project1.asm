assume cs:code

data segment
	db '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982', '1983'
	db '1984', '1985', '1986', '1987', '1988', '1989', '1990', '1991', '1992'
	db '1993', '1994', '1995'

	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514
	dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000

	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226
	dw 11542,14430,15257,17800
data ends

stack segment
	db 128 dup (?)
stack ends

row segment
	db 81 dup (0)
row ends

code segment
start:
	mov ax, row
	mov ds, ax

	mov ax, data
	mov es, ax

	mov ax, stack
	mov ss, ax
	mov sp, 128

	mov bx, 0  ; 人数偏移
	mov di, 0  ; 年和总收入偏移
	mov cx, 21
show_row:
	push cx
	mov si, 0
	mov cx, 81
	call memset
	pop cx

	mov ax, es:[di] ; 年
	mov [si], ax
	mov ax, es:2[di]
	mov 2[si], ax

	mov ax, es:84[di] ; 总收入
	mov dx, es:86[di]
	mov si, 20
	call dtoc

	div word ptr es:168[bx] ; 人均收入
	mov dx, 0
	mov si, 60
	call dtoc

	mov ax, es:168[bx] ; 人数
	mov dx, 0
	mov si, 40
	call dtoc

	push cx
	mov cx,80
	mov al, 0
	mov ah, 20h
	mov si, 0
	call replace
	pop cx

	push cx
	mov dx, 21
	sub dx, cx
	mov dh, dl
	mov dl, 0
	mov cl, 2
	mov si, 0
	call show_str
	pop cx

	add di, 4
	add bx, 2
	loop show_row

	mov ax,4c00h
	int 21h

; 功能：将 dword 型数据转变为表示十进制数的字符串，字符串以 0 为结尾符
; 参数：(ax)=dword 型数据的低 16 位
;       (dx)=dword 型数据的高 16 位
;		ds:si 指向字符串的首地址
; 返回：无
dtoc:
	push si
	push di
	push ax
	push cx
	push dx

	mov di, si ; save currect si for count
dtoc_1:
	mov cx,10
	call divdw

	add cx,30h
	push cx
	inc si

	mov cx,ax
	jcxz dtoc_2
	jmp dtoc_1
dtoc_2:
	mov cx,dx
	jcxz convert
	jmp dtoc_1

convert:
	; convert string
	mov [si],0
	mov cx,si
	mov si, di ; recover si
	sub cx,si
doconv:
	pop ax
	mov [si],al
	inc si
	loop doconv

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
	push es
	push ax
	push cx

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
show_str_0:
	mov cl, [si]
	jcxz ok
	mov es:[bx],cl
	inc bx
	mov es:[bx],dh
	inc bx
	inc si
	jmp show_str_0

ok:
	pop cx
	pop ax
	pop es
	pop dx
	pop bx
	ret

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

; 将内存空间置为 0
; 参数：cx 内存的字节数
;       ds:si 内存空间的开始偏移
; 返回：无
memset:
	push si
	push cx

memset_0:
	mov byte ptr [si], 0
	inc si
	loop memset_0

	pop cx
	pop si
	ret

; 替换字符串的值
; 参数：cx 内存的字节数
;       al: 源值
;       ah: 目的值
;       ds:si 内存空间的开始偏移
; 返回：无
replace:
	push si
	push cx
	push ax

replace_0:
	cmp al, byte ptr [si]
	jne replace_1
	mov byte ptr [si], ah
replace_1:
	inc si
	loop replace_0

	pop ax
	pop cx
	pop si
	ret

code ends

end start
