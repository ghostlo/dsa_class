data segment
	string1 db 'enter the first string (number<80) :',0DH,0AH,'$'
	string2 db 0dh,0ah,'enter the second string (number<80) :',0DH,0AH,'$'
	result1 db 0dh,0ah,'the two string are identical',0DH,0AH,'$'
	result2 db 0dh,0ah,'the two string are not identical',0DH,0AH,'$'
	re1 db 0dh,0ah,'the first one is large',0DH,0AH,'$'
	re2 db 0dh,0ah,'the second one is large',0DH,0AH,'$'
	in1 db 100
		db ?
		db 100 dup(?)
	in2 db 100
		db ?
		db 100 dup(?)
data ends

output macro dat
	lea dx,dat
	mov ah,9
	int 21h
endm

code segment
assume cs:code, ds:data
start:
	mov ax,data
	mov ds,ax

	lea dx,string1
	mov ah,09h
	int 21h

	lea dx,in1
	mov ah,0AH
	int 21h

	lea dx,string2
	mov ah,09h
	int 21h

	lea dx,in2
	mov ah,0AH
	int 21h

	lea si,in1
	lea di,in2
	inc si
	inc di
	mov ah,[si]
	mov al,[di]
	cmp ah,al
	ja notsame1
	cmp ah,al
	jb notsame2
	mov cl,al
	inc si
	inc di
ag:
	mov al,[si]
	mov ah,[di]
	cmp ah,al
	ja notsame1
	cmp ah,al
	jb notsame2
	inc si
	inc di
	loop ag
	output result1
	jmp extout
notsame1:
	output	result2
	output	re1
	mov ah,4ch
	int 21h
notsame2:
	output	result2	
	output	re2
extout:
	mov ah,4ch
	int 21h
code ends
end start

