typedef struct Struct_pulldown_unit 
{ 
   char name[30];                   // name 
   char status_unitnum;             // num 
   char config_position_x;          // position_x 
   CLASS_POPUP popup;               // popup 
   Struct_pulldown_unit *unit_next; // next 
   Struct_pulldown_unit *unit_prev; // prev 
}; 

class CLASS_PULLDOWN 
{ 
     protected: 
char config_position_y;                   // Y 
char config_forcolor;                     // FC 
char config_backgroundcolor;              // BC 
char config_barfccolor;                   // BAR FC 
char config_barbgrcolor;                  // BAR BC 

char status_select_main;                  // select main num 
char status_select_sub;                   // sub main num 
char status_unitcount;                    // unit counts 

Struct_pulldown_unit *unit_current;       // current unit 
Struct_pulldown_unit *unit_begin;         // begin 
Struct_pulldown_unit *unit_end;           // end 
     public: 
// main modules 
CLASS_PULLDOWN(char y,char fccol,char bgrcol 
      ,char barfc,char barbgrcol);// constructor 
CLASS_PULLDOWN(void);                     // constructor 
~CLASS_PULLDOWN(void);                    // deconstructor 
boolean operation(void);                  // operation 
  // select ok - TRUE 
  // select fail - FALSE 
// sub modules 
void unit_initialize(void);               // unit initialize 
void unit_append(char x,char *string); 
  // append data func 
void unit_destroy(void);                  // destroy end of unit 


void unit_subappend(char *string); 

void operation_curunitput(char barstatus);// current unit put func 
void operation_keyprocess(char ch);       // current key processing 

void get_selectnums(char *mainnum,char *subnum); // get num 
}; 

CLASS_PULLDOWN::CLASS_PULLDOWN(char y,char fccol,char bgrcol 
      ,char barfc,char barbgrcol) 
{ 
   // config field set 
   CLASS_PULLDOWN::config_position_y = y;              // Y 
   CLASS_PULLDOWN::config_forcolor = fccol;            // FC 
   CLASS_PULLDOWN::config_backgroundcolor = bgrcol;    // BC 
   CLASS_PULLDOWN::config_barfccolor = barfc;          // BAR FC 
   CLASS_PULLDOWN::config_barbgrcolor = barbgrcol;     // BAR BC 

   CLASS_PULLDOWN::status_select_main = 0;             // num(main) 
   CLASS_PULLDOWN::status_select_sub = 0;              // num(sub) 
   CLASS_PULLDOWN::status_unitcount = 0;               // unit counts 

   CLASS_PULLDOWN::unit_initialize();                  // unit initialize 
   return; 
} 

CLASS_PULLDOWN::CLASS_PULLDOWN(void) 
{ 
   // config field set 
   CLASS_PULLDOWN::config_position_y = 0;              // Y 
   CLASS_PULLDOWN::config_forcolor = 0;                // FC 
   CLASS_PULLDOWN::config_backgroundcolor = 0;         // BC 
   CLASS_PULLDOWN::config_barfccolor = 0;              // BAR FC 
   CLASS_PULLDOWN::config_barbgrcolor = 0;             // BAR BC 

   CLASS_PULLDOWN::status_select_main = 0;             // num(sub) 
   CLASS_PULLDOWN::status_select_sub = 0;              // num(sub) 
   CLASS_PULLDOWN::status_unitcount = 0;               // unit counts 

   CLASS_PULLDOWN::unit_initialize();                  // unit initialize 
   return; 
} 

CLASS_PULLDOWN::~CLASS_PULLDOWN(void) 
{ 
   // deconstructor 
   register int count; 
   CLASS_PULLDOWN::unit_current = CLASS_PULLDOWN::unit_begin; 
   // status_unitcount+unit_begin(1) 
   for( count=0 ; count<=CLASS_PULLDOWN::status_unitcount ; count++ ) 
   { 
      delete CLASS_PULLDOWN::unit_current; 
      CLASS_PULLDOWN::unit_current 
      = CLASS_PULLDOWN::unit_current->unit_next; 
   } 
   return; 
} 

void CLASS_PULLDOWN::unit_initialize(void) 
{ 
   // allocation unit 
   CLASS_PULLDOWN::unit_begin = new Struct_pulldown_unit; 

   if( CLASS_PULLDOWN::unit_begin != NULL ) 
   { 
      // allocation success : data setting 
      CLASS_PULLDOWN::unit_begin->name[0] = '\0'; 
      CLASS_PULLDOWN::unit_begin->status_unitnum = 0; 
      CLASS_PULLDOWN::unit_begin->unit_prev = CLASS_PULLDOWN::unit_end; 

      // initialize unit_current 
      CLASS_PULLDOWN::unit_current = CLASS_PULLDOWN::unit_begin; 
   } 
   else 
   { 
      printf(" Memory allocaiton failured.\n"); 
      asm mov ah,1Ch; // exit 
      asm int 21h; 
   } 
   return; 
} 

void CLASS_PULLDOWN::unit_append(char x,char *string) 
{ 
   // allocation 
   Struct_pulldown_unit *unit_temp = new Struct_pulldown_unit; 

   if( unit_temp != NULL ) 
   { 
// allocation success : data set 
strcpy( unit_temp->name,string ); 
unit_temp->config_position_x = x; 
unit_temp->status_unitnum = ++CLASS_PULLDOWN::status_unitcount; 

// link - link between unit_current and unit_temp. 
//        and change unit_current. 
CLASS_PULLDOWN::unit_current->unit_next = unit_temp; 
unit_temp->unit_prev = CLASS_PULLDOWN::unit_current; 

// unit_temp next link ( end link ) 
unit_temp->unit_next = CLASS_PULLDOWN::unit_begin->unit_next; 

// begin unit link data change 
CLASS_PULLDOWN::unit_end = unit_temp; 
CLASS_PULLDOWN::unit_begin->unit_prev = CLASS_PULLDOWN::unit_end; 

CLASS_PULLDOWN::unit_current = unit_temp; 

// set popup data 
CLASS_PULLDOWN::unit_current 
->popup.setinitdata( CLASS_PULLDOWN::unit_current 
    ->config_position_x-1, 
    CLASS_PULLDOWN::config_position_y+1, 
    15,1,15,2,64|16); 

   } 
   else 
   { 
printf("Memory allocation error.\n"); 
asm mov ah,1Ch; 
asm int 21h; 
   } 
   return; 
} 

void CLASS_PULLDOWN::unit_destroy(void) 
{ 
   // destroy end of unit 
   if( CLASS_PULLDOWN::status_unitcount >= 1 ) // data exist check. 
   { 
      // destroy unit 
      CLASS_PULLDOWN::unit_current->unit_prev->unit_next 
= CLASS_PULLDOWN::unit_begin->unit_next; 
      CLASS_PULLDOWN::status_unitcount--; // count decrease. 
      delete CLASS_PULLDOWN::unit_current; 

      // link cut 
      CLASS_PULLDOWN::unit_current = unit_current->unit_prev; 

      // setting unit_end 
      CLASS_PULLDOWN::unit_end = unit_current; 

      // begin unit link data change 
      CLASS_PULLDOWN::unit_begin->unit_prev = CLASS_PULLDOWN::unit_end; 
   } 
   return; 
} 

void CLASS_PULLDOWN::operation_curunitput(char barstatus) 
{ 
   // current unit put func 
   char *putstring; 

   putstring = CLASS_PULLDOWN::unit_current->name; 

   // set color 
   if( barstatus == 1 ) // if barstatus is 1? 
     textattr( (CLASS_PULLDOWN::config_barbgrcolor << 4) 
| CLASS_PULLDOWN::config_barfccolor ); 
   else 
     textattr( (CLASS_PULLDOWN::config_backgroundcolor << 4) 
| CLASS_PULLDOWN::config_forcolor ); 

   gotoxy(CLASS_PULLDOWN::unit_current->config_position_x+1 
 ,CLASS_PULLDOWN::config_position_y+1); 

   while( *putstring ) 
   { 
     if( *putstring == '@' ) 
     { 
textcolor(14); 
*putstring++; 
     } 
     else 
     { 
cprintf("%c",*putstring++); 
textcolor( barstatus==0 ? CLASS_PULLDOWN::config_forcolor : 
 CLASS_PULLDOWN::config_barfccolor ); 
     } 
   } 
   return; 
} 

boolean CLASS_PULLDOWN::operation(void) 
{ 
   unsigned char getkey; 
   unsigned int  showpopup = 0; 
   register int c; 
   // operation 
   CLASS_PULLDOWN::unit_current = CLASS_PULLDOWN::unit_begin; 
   for( c=1 ; c<=CLASS_PULLDOWN::status_unitcount ; c++ ) 
   { 
      CLASS_PULLDOWN::unit_current 
      = CLASS_PULLDOWN::unit_current->unit_next; 
      CLASS_PULLDOWN::operation_curunitput(0); 
   } 

   CLASS_PULLDOWN::unit_current = CLASS_PULLDOWN::unit_begin->unit_next; 
   CLASS_PULLDOWN::operation_curunitput(1); 
   while(1) 
   { 
      getkey = getch(); 
      if( getkey == 0 ) // is extend ascii 
      { 
  getkey = getch(); 
  CLASS_PULLDOWN::operation_keyprocess(getkey); 
      } 
      else 
      { 
  while(1) 
  { 
     if( getkey == 13 ) 
     { 
 if( showpopup == 1 ) return TRUE; 
 if( showpopup == 0 ) 
 { 
     showpopup = 1; 
     while(1) 
     { 
getkey = CLASS_PULLDOWN::unit_current->popup.operation(); 
if( getkey == 27 || getkey == 13 ) break; 
if( getkey == 75 || getkey == 77 ) 
   CLASS_PULLDOWN::operation_keyprocess(getkey); 
else 
   break; 
     } 
     if( getkey == 0 ) showpopup = 0; 
     if( getkey == 27 ) 
     { 
CLASS_PULLDOWN::unit_current->popup.recoverbackground(); 
showpopup = 0; 
     } 
     if( getkey == 13 ) 
     { 
CLASS_PULLDOWN::status_select_main 
= CLASS_PULLDOWN::unit_current->status_unitnum; 
CLASS_PULLDOWN::unit_current 
->popup.get_selectnum( &status_select_sub ); 
return TRUE; 
     } 
     getkey = 0; // getkey initialize 
 } 
     } 
     if( getkey != 13 ) break; 
  } 
  if( getkey == 27 ) return FALSE; 
      } 
   } 
} 

void CLASS_PULLDOWN::operation_keyprocess(char ch) 
{ 
   // current key processing 
   switch(ch) 
   { 
case 75: 
   CLASS_PULLDOWN::operation_curunitput(0); 
   if( CLASS_PULLDOWN::unit_current->unit_prev->status_unitnum 
== 0 ) // it's head 
CLASS_PULLDOWN::unit_current 
= CLASS_PULLDOWN::unit_current->unit_prev->unit_prev; 
   else 
CLASS_PULLDOWN::unit_current 
= CLASS_PULLDOWN::unit_current->unit_prev; 
   CLASS_PULLDOWN::operation_curunitput(1); 
   break; 
case 77: 
   CLASS_PULLDOWN::operation_curunitput(0); 
   CLASS_PULLDOWN::unit_current 
    = CLASS_PULLDOWN::unit_current->unit_next; 
   CLASS_PULLDOWN::operation_curunitput(1); 
   break; 
   } 
   return; 
} 

void CLASS_PULLDOWN::unit_subappend(char *string) 
{ 
   CLASS_PULLDOWN::unit_current->popup.unit_append(string); 
   return; 
} 

void CLASS_PULLDOWN::get_selectnums(char *mainnum,char *subnum) 
{ 
   // get set icon 
   *mainnum = CLASS_PULLDOWN::status_select_main; 
   *subnum  = CLASS_PULLDOWN::status_select_sub; 
   return; 
} 
  