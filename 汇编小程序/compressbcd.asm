DATA        SEGMENT PARA
BLOCK       DB          52H, 14H, 56H, 85H, 34H
            DB          63H, 38H, 70H, 18H, 69H
COUNT       EQU         $-OFFSET BLOCK
MAX         DB          2 DUP(?)
DATA        ENDS
 
CSEG        SEGMENT     PARA 'CODE'
START 	     PROC  FAR
            ASSUME            CS:CSEG, DS:DATA
            MOV         AX, DATA
            MOV         DS, AX
	      MOV         AH, 00H
            MOV         SI, OFFSET BLOCK
            MOV         BX, OFFSET MAX
            MOV         CX, COUNT
            MOV         DL, [SI]
	      MOV         DH, 00H
            INC         SI
COMP: 
            LODSB
            CMP         AX, DX
            JL          NEXT
            MOV         DX, AX
NEXT: 
            LOOP        COMP
            MOV         DH, DL
            MOV         Al, DL
            AND         AL, 0F0H
	      MOV         CL, 04H
            SHR         AL, CL
            ADD         AL, 30H
            MOV         [BX], AL
            MOV         AL, DL
            AND         AL, 0FH
            ADD         AL, 30H
            MOV         [BX+1],AL              
PRINT:            
            MOV         BX, OFFSET MAX
            MOV         DL, [BX]
            MOV         AH, 2
            INT         21H
            MOV         DL, [BX+1]
            INT         21H
            MOV         AH, 4CH
            INT         21H

 START      ENDP
 CSEG ENDS
      END   START
