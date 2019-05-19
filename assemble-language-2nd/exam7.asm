assume cs:code,ds:data

data segment
	db '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982', '1983'
	db '1984', '1985', '1986', '1987', '1988', '1989', '1990', '1991', '1992'
	db '1993', '1994', '1995'

	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514
	dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000

	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226
	dw 11542,14430,15257,17800
data ends

table segment
	db 21 dup ('year summ ne ?? ')
table ends

code segment
start:
	mov ax, data
	mov ds, ax

	mov ax, table
	mov es, ax

	mov bx, 0  ; 人数偏移
	mov si, 0  ; 年和总收入偏移
	mov di, 0  ; 表偏移
	mov cx, 21
s:
	mov ax, [si] ; 年
	mov es:[di], ax
	mov ax, 2[si]
	mov es:2[di], ax

	mov ax, 84[si] ; 总收入
	mov es:5[di], ax
	mov dx, 86[si]
	mov es:7[di], dx

	div word ptr 168[bx] ; 人均收入
	mov es:13[di],ax

	mov ax, 168[bx] ; 人数
	mov es:10[di],ax

	add di, 16
	add si, 4
	add bx, 2
	loop s

	mov ax,4c00h
	int 21h
code ends

end start
