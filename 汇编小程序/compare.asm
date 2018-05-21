STACK1 SEGMENT para 'STACK'
      DB 200 DUP(?)
STACK1 ENDS

DATA  SEGMENT
BUF   DB 20 dup(0)           ;���ת��������� 
N     dw   ?
MAX   DB ?
MIN   DB ?

INPUT  db  0ah,0dh,'please choose the max and min numbers from the input numbers'
       db   0ah,0dh,'if you want to quit ,please press..q/Q...',0ah,0dh
       db   'press other key to input numbers$'
input1  DB 0ah,0dh,'please input numbers(0~255) seperated by ",":',0ah,0dh,'$'
output  db 0ah,0dh,'the max number:',0ah,0dh,'$'
output1 db 0ah,0dh,'the min number:',0ah,0dh,'$'
ERROR_MESS DB 'INPUT ERROR ,PLEASE INPUT AGAIN',0AH,0DH,'$'
buf0     db 7 dup(0)               ;���һ��ʮ�����ַ���
BUF2     DB 7 DUP(0)                 
BUF1    DB 100                      ;�ַ�������
        DB  ?
        DB 100 DUP(0)
dat     db 10
SIGN   DB 0                        ;�Ƿ�����������ݴ�����
SIGN0  DB 0                          ;�Ƿ���� 

                     
DATA  ENDS
CODE  SEGMENT
      ASSUME CS:CODE,DS:DATA,SS:STACK1
START:
      MOV AX,DATA
      MOV DS,AX
      
L0:   LEA DX,INPUT                  ;������ʾ
      MOV AH,9
      INT 21H
                                          
      MOV AH,08h
      INT 21H
      cmp AL,'Q'
      jE   exit
      cmp AL,'q'
      je   exit 

reinput:LEA BX, buf
      MOV SIGN,0
      MOV SIGN0,0
      mov N,0                               
      LEA DX,INPUT1                  ;������ʾ
      MOV AH,9
      INT 21H
      LEA DX,BUF1                                    
      MOV AH,10
      INT 21H

      LEA DI,BUF1+2                  ;��ʼ�������������
r1:  LEA SI,BUF0
     MOV CX,0
r2:  MOV DL,[DI]
     INC DI
     CMP DL,0DH
     JNE AA
     INC SIGN
     JMP A0
AA:  CMP DL,','
     JE  A0
     MOV [SI], DL
     INC  SI
     INC  CX
     JMP  r2
         
A0:    
    LEA  SI,BUF0
    MOV BP,CX
    CALL F10T2
    cmp  sign0,-1
    je   et
    mov [bx],al
    add   bx,1
    inc   n 
    cmp  sign,1
    je       end0
     
    jmp    r1
EXIT: MOV AH,4CH
      INT 21H  

et:   lea dx,error_mess                         ;������ʾ
      mov ah,9
      int 21h
      jmp  reinput
end0:  mov bp,n

     MOV SI,OFFSET BUF  ;������ַSI
     MOV CX,bp          ;���ݸ���CX
     
     CALL MAXMIN
     MOV MAX,BH       ;�������ֵ
     MOV MIN,BL         ;������Сֵ
     lea dx,output       ;������    
     mov ah,9
     int 21h
     mov al,max
     call f2t10
     
     lea dx,output1
     mov ah,9
     int 21h
     mov al,min
     call f2t10
        
     jmp l0         
MAXMIN PROC
     PUSH AX
     
     MOV BH,[SI]     ;����һ������BH,BL
     MOV BL,BH
     DEC CX          ;��Ƚϵ����ݸ�����1
     
A1:  INC SI
     MOV AL,[SI] 
     CMP AL,BH
     JBE A2
     MOV BH,AL  ;�磨AL��>(BH),��AL��=BH
     JMP A3
A2:  CMP AL,BL  
     JAE A3
     MOV BL,AL  ;�磨AL��<(BL),��AL��=BL
A3:  LOOP A1     ;ѭ����ֱ��CX=0       
     
     POP AX
     RET
MAXMIN ENDP
;*************************************
; ʮ����ת��Ϊ�������ӳ���           *
;��ڲ���  SI--Ҫת�����ַ�����ַ    * 
;          CX--ʮ����λ��            *
;���ڲ���  AL--ת��Ϊ�Ķ�������      * 
;************************************
F10T2   PROC
     PUSH  BX
     MOV Ax,0
     MOV BL,[SI]
     CMP BL,'+'
     JnZ next3
     dec cx  
m:
     INC SI
     MOV BL,[SI]
NEXT3:    CMP BL,30H
     JB     D1
     cmp bl,39h
     ja  d1
     sub bl,30h
     mul dat
     jo  d1
     add al,bl
     jc   d1
     dec cx
     jne  m
            
QQ:        
     pop  bx
     ret    
d1:  mov sign0,-1
     jmp    qq
f10t2     ENDP

;*************************************
; ������ת��Ϊʮ�����ӳ���           *
;��ڲ���  AL--Ҫת���Ķ���������    * 
;���ڲ���  BUF2--���ת��Ϊ��        * 
;                 ʮ�����ַ���        * 
;*************************************
      

f2t10   proc
    push bx
    push dx
    push si
    MOV AH,0
    lea si,buf2
    mov bx,10
    call radix1
    mov [si],byte ptr '$'
    mov dx,offset buf2
    mov ah,9
    int 21h
    pop si
    pop dx
    pop bx
    ret
f2t10   endp
;*************************************
; ����ת���������                   *
;��ڲ���  AX--Ҫת���Ķ���������    * 
;          BX--Ҫת����BX���Ƶ�����  *
;���ڲ���                            * 
;                                     * 
;*************************************
      
radix1    proc
    push cx
    push dx
    mov cx,0
lop1:   
    mov dx,0
    div bx
    push dx
    inc cx
    or ax,ax
    jne lop1
lop2:   
    pop ax
    cmp al,10
    jb   l3
    add al,7
    add al,30h
l3:     
    add al,30h
    mov [si],al
    inc si
    dec cx
    jne lop2
    pop dx
    pop cx
    ret
radix1    endp

CODE   ENDS
END START   
