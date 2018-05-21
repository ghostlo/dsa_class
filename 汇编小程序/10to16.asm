DATA        SEGMENT     PARA
STRING      DB    0DH,0AH,'Please Input a number $'
RESULT      DB    0DH,0AH,'The result is $'
ER          DB    0DH,0AH,'INPUT OUT OF RANGE! $'
ERR         DB    0DH,0AH,'INPUT ERROR! $'
DATA        ENDS

CSEG        SEGMENT     PARA 'CODE'
MAIN        PROC FAR
ASSUME CS:CSEG, DS:DATA

	      MOV         AX,DATA
            MOV         DS,AX

REPEAT:
      	LEA DX,STRING
            MOV AH,09H
       	INT 21H

	      CALL DEC2BIN   ;十进制转换为二进制

	      CMP DX,0
	      JG REPEAT

             LEA DX,RESULT
	 	 MOV AH,09H
	 	 INT 21H

             CALL BIN2HEX   ;二进制转换为十六进制
             MOV DL,0DH		;回车与换行
             MOV AH,2
             INT 21H
             MOV DL,0AH
             MOV AH,2
             INT 21H
             JMP REPEAT
EXITT:
		 RET
MAIN         ENDP

;十进制转换二进制，结果放在寄存器BX中
DEC2BIN      PROC NEAR
             MOV BX,0
KEYIN:           
		 MOV AH,1
             INT 21H
             CMP AL,0AH
             JE EXIT
             CMP AL,0DH		;回车检测
             JE EXIT
             SUB AL,30H
             JL EXIT2
             CMP AL,9
             JG EXIT2
             CBW
             XCHG AX,BX
             MOV DX,0
             MOV CX,10
             MUL CX
             CMP DX,0
             JG EXIT1
             XCHG AX,BX
             ADD BX,AX
             JMP KEYIN
EXIT:  
		 RET
EXIT1:  
		 LEA DX,ER
	 	 MOV AH,09H
	 	 INT 21H
		 RET
EXIT2:  
		 LEA DX,ERR
	 	 MOV AH,09H
	 	 INT 21H
	 	 MOV DX,1
		 RET

DEC2BIN      ENDP

;二进制转换为十六进制，把BX中的值按高到低先后，以4个二进制位为一个16进制数，搭配成ASCII码输出
BIN2HEX      PROC NEAR
             MOV CH,4
ROTATE:      MOV CL,4
             ROL BX,CL
             MOV AL,BL
             AND AL,0FH
             ADD AL,30H
             CMP AL,3AH
             JL PRINT
             ADD AL,07H
PRINT:           
		 MOV DL,AL
             MOV AH,2
             INT 21H
             DEC CH
             JNZ ROTATE
         	 RET
BIN2HEX      ENDP

CSEG     ENDS
                 END MAIN