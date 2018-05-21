JUMP16         MACRO      selector,offsetv
               DB         0EAH
               DW         offsetv
               DW         selector
               ENDM   
Descriptor     STRUC
               limitl     dw 0
               basel      dw 0
               basem      db 0
               attrib     dw 0
               baseh      db 0
Descriptor     ENDS
Data           Segment    use16
               gdt0       Descriptor <>   ;GDT表的开始
               DataSel    = $-gdt0
               DataDes    Descriptor <0ffffh,,,92H,>  
               CodeSel    = $-gdt0
               CodeDes    Descriptor <0ffffh,,,98H,>    
               VideoSel   = $-gdt0
               VideoDes   Descriptor <0ffffh,8000H,0BH,92H,>   
               GdtLen     = $-gdt0  
               GdtPtr     dw GdtLen
                          dd 0
               Mess       db 'Now Is In Protect Mode.',0
Data           ends
;=============================================================
Code           Segment    use16
                  assume cs:Code,ds:Data
Start:         xor       eax,eax
               mov       ax,Data
               mov       ds,ax
               shl       eax,4
               mov       dword ptr [GdtPtr+2],eax    
               mov       DataDes.basel,ax    ;初始化数据段描述符
               shr       eax,16
               mov       DataDes.basem,al
               mov       DataDes.baseh,ah
               xor       eax,eax                ;初始化代码段描述符
               mov       ax,Code
               shl       eax,4
               mov       CodeDes.basel,ax
               shr       eax,16
               mov       CodeDes.basem,al
               mov       CodeDes.baseh,ah
               lgdt      qword ptr GdtPtr   ;Load GDT
               cli
               mov       eax,cr0                ;转到保护模式模式
               or        eax,1
               mov       cr0,eax
               JUMP16    CodeSEL,<offset Code16>
Code16:        mov       ax,DataSel
               mov       ds,ax
               mov       ax,VideoSel
               mov       es,ax
               mov       si,offset Mess
               mov       di,2284
               cld
               mov       ah,1eh
Load:          lodsb
               cmp       al,0
               jz        ReadyToReal
               stosw
               jmp       Load
ReadyToReal:   mov       eax,cr0  ;返回实模式
               and       eax,0fffffffeh
               mov       cr0,eax
               JUMP16    <seg Real>,<offset Real>    
Real:          sti
               mov      ax,Data
               mov      ds,ax
               mov      es,ax
               mov      ax,4c00h
               int      21h
Code           ends
               end      Start