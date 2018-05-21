DATA        SEGMENT     PARA
STRING      DB    0DH,0AH,'Please Input a number :$'
STRINGG     DB    0DH,0AH,'Press - or = to exit $'
ERRSTR      DB    0DH,0AH,'ERROR! PLEASE INPUT TWO DIGIT!',0DH,0AH,'$'
RESSTR      DB    0DH,0AH,'The square is $'
DATA        ENDS
 
CSEG        SEGMENT     PARA 'CODE'
START       PROC        FAR
            ASSUME      CS:CSEG, DS:DATA

            MOV         AX,DATA
            MOV         DS,AX
            LEA         DX,STRINGG
            MOV         AH,09H            ;显示Press - or = to exit
            INT         21H

            LEA         DX,STRING
            MOV         AH,09H            ;显示input a number
            INT         21H

            MOV         AH,01H            ;输入高位
            INT         21H

            CMP         AL,'-'            ;加减退出
            JZ          EXIT100
            CMP         AL,'='
            JZ          EXIT100

            CMP         AL,'0'            ;输入错误检测
            JB          ERROR
            CMP         AL,'9'
            JA          ERROR

            SUB         AL,30H            ;转换为0~9

            MOV         CL,10D
            MUL         CL                ;十位数跟10d，即AH相乘，结果放在AX上
            MOV         BL,AL
            MOV         AH,01H
            INT         21H

            CMP         AL,'0'            ;输入错误检测
            JB          ERROR
            CMP         AL,'9'
            JA          ERROR

            SUB         AL,30H
            
            ADD         AL,BL             ;已输入的十位数与10的积加上个位数，即结果为输入2位数的2进制数
            MUL         AL                ;al*al的结果放在AX处
            MOV         BX,AX             ;将结果放在BX处
            CALL        HEX_DEC
            JMP         EXIT
ERROR:
            MOV         DX,OFFSET ERRSTR
            MOV         AH,09H
            INT         21H
EXIT: 
            CALL START
EXIT100:
            RET

HEX_DEC PROC NEAR
            MOV         DX,OFFSET RESSTR
            MOV         AH,09H
            INT         21H
            MOV         SI,0
            MOV         CX,1000D
            CALL        DEC_DIV
            MOV         CX,100D
            CALL        DEC_DIV
            MOV         CX,10D
            CALL        DEC_DIV
            MOV         CX,1D
            CALL        DEC_DIV
            CMP         SI,0
            JNE         EXIT2
            MOV         DL,30H
            MOV         AH,2
            INT         21H
EXIT2:
            RET
HEX_DEC ENDP

DEC_DIV PROC NEAR
            MOV         AX,BX
            MOV         DX,0
            DIV         CX          ;DX,AX DIV CX
            MOV         BX,DX       ;余数存入BX
            CMP         SI,0
            JNZ         PRINT
            CMP         AL,0
            JZ          EXIT1
            MOV         SI,1
PRINT:
            MOV         DL,AL
            ADD         DL,30H
            MOV         AH,02H
            INT         21H
EXIT1:
            RET
DEC_DIV ENDP

START ENDP
 CSEG ENDS
      END   START
