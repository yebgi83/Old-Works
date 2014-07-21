/* 제작 연습*/ 
/* Memory manager */ 
/* 제작 : 이강용(dragonhi) */ 
/* Brightieng Soft Team 팀장 */ 
/* 인클루드 화일의 부름 */ 
#include /* 기본입출력 */ 
#include 
void far *XMS_function_pointer; /* XMS함수 (포인터) */ 

class MEMORY_Information 
{ 
   protected: 
      void InitXMS_Function(); /* XMS함수의 세그먼트와 오프셋을 알아내는 함수 */ 
      void InitXMS_LoadVersion(); /* 버전을 불러내는 함수 */ 
   public: 
      int XMSmajor,XMSminor; /* 버전의 상위와 하위 버전이 들어갈 장소 */ 
      int maxfreeXMS;        /* 사용가능한 XMS최대용량 */ 
      int InitXMS();        /* XMS의 초기화 */ 
      void GetFreeXMS();    /* 사용가능한 XMS의 총 용량이 나오게 된다 */ 
}; 

int MEMORY_Information :: InitXMS() 
{ 
   int success; 
   asm mov ax , 4300h; 
   asm int 2fh; 
   /* al의 값이 0x80이면 HIMEM가 상주했다는 뜻이다 */ 
   asm mov success, ax; 
   if ( (success & 0x80) == 0x80 ) 
   { 
      /* XMS함수의 위치를 찾아낸다. */ 
      MEMORY_Information :: InitXMS_Function(); 
      MEMORY_Information :: InitXMS_LoadVersion(); 
      MEMORY_Information :: GetFreeXMS(); 
      return 1; /* HIMEM상주 */ 
   } 
   else 
      return 0; /* HIMEM상주안했음 */ 
} 
void MEMORY_Information :: InitXMS_Function() 
{ 
   int segment,_offset; 
   /* XMS함수의 세그먼트와 오프셋의 위치를 알아낸다. */ 
   asm mov ax, 4310h; 
   asm int 2fh; 
   asm mov segment, es; 
   asm mov _offset, bx; 
   XMS_function_pointer = MK_FP(segment,_offset); 
} 
void MEMORY_Information :: InitXMS_LoadVersion() 
{ 
   unsigned int version; 
   asm mov ah , 0; 
   asm call dword ptr [XMS_function_pointer]; /* XMS함수 가동 */ 
   /* ax와 bx로 빠져나온다 */ 
   asm mov version , ax; /* 버전내용을 부른다. */ 
   /* version의 상위는 상위버전 하위부분은 하위 버전이다 */ 
   XMSmajor = (version & 0xff00) >> 8; 
   XMSminor = (version & 0x00ff); 
} 
void MEMORY_Information :: GetFreeXMS() 
{ 
   int t; 
//  /* CMOS RAM의 오프셋 30h와 31h에 내용을 부른다 */ 
//  /* 입출력 포트 0x70 <-- CMOS RAM관련 */ 
//  /* 입출력 포트 0x71로 결과가 나온다. */ 
//  outportb(0x70 , 0x31);   /* 상위 바이트 로드 */ 
//  maxfreeXMS = inportb(0x71) * 256; 
//  outportb(0x70 , 0x30);   /* 하위 바이트 */ 
//  maxfreeXMS += inportb(0x71); 
   asm mov ah , 8; 
   asm call dword ptr [XMS_function_pointer]; /* XMS함수 가동 */ 
   /* ax와 bx로 빠져나온다 */ 
   asm mov t , ax; /* 버전내용을 부른다. */ 
   /* version의 상위는 상위버전 하위부분은 하위 버전이다 */ 
   maxfreeXMS = t; 
} 
