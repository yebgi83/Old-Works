.MODEL LARGE 
.CODE 
BeginCode: 
  ; *Initialize process 
    ; Set segment 
    MOV AX,0A000h 
    MOV ES,AX   ; Extra segment setting 

    ; Set video mode ( 800*600*256 ) 
    MOV AX,4F02h 
    MOV BX,0103h 
    INT 10h 

  ; Program Main 
    CALL ProgramMain 
    CALL PaletteSet 
  
  ; Key - press any key. 
  MOV AH,10h 
  INT 16h 
  
  ; Remove video mode 
  MOV AX,0003h 
  INT 10h 

  ; *Exit program 
  MOV AH,4Ch 
  INT 21h 
                                
PaletteSet: 
  MOV AX,PALETTETABLE 
  MOV DS,AX 
  XOR SI,SI 
  MOV CX,256 
  XOR BL,BL ; Color 
  CLD 
Loop_PaletteSet001:       
  MOV DX,3C8h 
  MOV AL,BL 
  OUT DX,AL 
  MOV DX,3C9h 
  LODSB 
  SHR AL,1 
  SHR AL,1 
  OUT DX,AL 
  LODSB 
  SHR AL,1 
  SHR AL,1 
  OUT DX,AL 
  LODSB 
  SHR AL,1 
  SHR AL,1 
  OUT DX,AL 
  INC BL 
LOOP Loop_PaletteSet001 
RET 

ProgramMain: 
  MOV AX,KJHGRP1 ; Set KJHGRP1 segment 
                  KJH? -_-; 
  MOV DS,AX 
  XOR SI,SI 
  
  MOV AX,1       ; SEGMENT COUNT 
  PUSH AX 

  Loop000:     
     MOV CX,160 
     Loop001:     
        ; *Put 200,y -> 600,y 
  
        ; Check both (200,y) and (600,y) are similar position of bank. 
          MOV BX,200 
          MOV DX,CS:Y 
          Call GetBankAndPosition ; get logical position through BX,DX. 
          PUSH DX   save position 
          PUSH BX   save bank 
      
          MOV BX,600 
          MOV DX,CS:Y 
          Call GetBankAndPosition ; get logical position through BX,DX. 
  
        ; Compare Before value and current value 
          POP DX   pop bank <-- This's important 
          
          CMP BX,DX; compare 
          ; JMP each routine 
          JE Putroutine001   Jmp Putroutine001 If both a and b are similar bank. 
          JNE Putroutine002 ; Jmp Putroutine001 If both a and b are another bank. 
  ReturnJMP001: 
       INC CS:Y           increase Y 
        INC [0001] is impossible. 
        Compiler required exact type. 
        Therefore INC BYTE PTR [0001] is possible. 
     LOOP Loop001 
      
      Put completed 
     POP AX ; POP SEGMENT COUNT 
     INC AX 
     PUSH AX ; SAVE POP SEGMENT COUNT 
     CMP AX,2 
     JE SegmentSet2 
     CMP AX,3 
     JE SegmentSet3 
     CMP AX,4 
     JE SegmentSet4 
     CMP AX,5 
     JE SegmentSet5 
ReturnJMP002: 
     XOR SI,SI 
  JMP Loop000 

SegmentSet2: 
  MOV AX,KJHGRP2 ; Set KJHGRP2 segment 
                  KJH? -_-; 
  MOV DS,AX 
  JMP ReturnJMP002 
SegmentSet3: 
  MOV AX,KJHGRP3 ; Set KJHGRP2 segment 
                  KJH? -_-; 
  MOV DS,AX 
  JMP ReturnJMP002 
SegmentSet4: 
  MOV AX,KJHGRP4 ; Set KJHGRP4 segment 
                  KJH? -_-; 
  MOV DS,AX 
  JMP ReturnJMP002 
SegmentSet5: 
  POP AX 
  RET 

Putroutine001: 
  ; Put routine when similar bank. 
  ; Get data 
      
    ; Bank set 
    MOV AX,04F05h 
    XOR BX,BX 
    INT 10h 

    ; ES:DI ( defination ) setting 
    POP DI ; pop position 

    ; Put pixel 
    PUSH CX 
    MOV CX,400 
    CLD 
    REP MOVSB ; Repeat STOre String Byte 
    POP CX     Remove CX 

  JMP ReturnJMP001 ; Return Main Routine 

Putroutine002: 
  ; Put routine when another bank. 
    XOR BX,BX   ; bank setting prepare 
    POP DI ; pop position 
    CLD 
    PUSH CX 
    MOV CX,400 
    Loop003: 
      ; ES:DI ( defination ) setting 
      CMP DI,0FFFFh 
      JE BankNumIncrease 
      MOVSB 
    LOOP Loop003 
    POP CX 
  
  JMP ReturnJMP001 ; Return Main Routine 
BankNumIncrease: 
  ; Set Bank 
  MOV AX,4F05h 
  INC DX ; Increase DX 
  INT 10h 
  XOR DI,DI 
  LOOP Loop003 

GetBankAndPosition: 
  ; Get Bank And Position 
  ; Get data = BX,DX <-- physical position(X,Y) 
  ; Return data = BX,DX <-- logical position(bank,position) 
          
  ; 1. save position of byte 
    ; 800 mul 
    MOV AX,800 
    MUL DX       ; AX = 800*DX 
    ; AX is low region in mulrate value 
    ; DX is high region in mulrate value 
    ADD AX,BX     AX = AX+BX 
    ADC DX,0     ; Carry add 
    ; AX is position of byte 
  ; 2. save logical of byte 
    ; hmm , already save logical of byte 
    ; AX is low region in mulrate value 
    ; and logical position of byte 
    ; DX is high region in mulrate value 
    ; and logical position of bank ( 1bank = 64K(65536Bytes) ) 
    MOV BX,DX 
    MOV DX,AX 
  RET ; Return routine 

  Y DW 0 ; Y position 
.STACK 
  DB 512 DUP (0) 

.DATA   
  INCLUDE KHJPAL.ASM ; load Kim hyun ju picture 
  INCLUDE KHJ.ASM ; load Kim hyun ju picture 

END BeginCode 
