data segment  
        str1 db 512 dup('$')  
        len  equ $-str1         ;获取str1的长度  
        str2 db 512 dup('$')  
        matc db 'identical$'  
        nomh db 'Not identical$'  
data ends  
  
code segment  
assume ds:data,cs:code  
start:  
        mov ax,data  
        mov ds,ax  
        mov es,ax  
  
        mov cx,len          ;设置循环次数为str1的长度  
  
        mov di,offset str1  
        mov si,offset str2
  
        mov ah,0ah          ;输入第一个字符串  
        mov dx,offset str1  
        int 21h  
  
        mov ah,02h          ;回车换行  
        mov dl,0dh  
        int 21h  
        mov dl,0ah  
        int 21h  
          
        mov ah,0ah          ;输入第二个字符串  
        mov dx,offset str2  
        int 21h  
  
        mov ah,02h          ;回车换行  
        mov dl,0dh  
        int 21h  
        mov dl,0ah  
        int 21h
                       
        repz cmpsb          ;当前字符相同则继续循环  
        jz match  
        jnz nomch  
  
        match:              ;字符串相同则显示match  
        mov ah,09h  
        mov dx,offset matc  
        int 21h  
        jmp done  
  
        nomch:              ;字符串不同则显示Nomatch  
        mov ah,09h  
        mov dx,offset nomh  
        int 21h  
        jmp done  
  
        done:               ;返回操作系统  
        mov ah,4ch  
        int 21h  
          
code ends  
end start  