struct Struct_popup_unit 
{ 
   char name[30];           // name 
   char status_unitnum;     // unit num 
   char config_ignoreunit;  // is ignore unit? 
   Struct_popup_unit *unit_next; // two link list -- next address 
   Struct_popup_unit *unit_prev; // two link list -- prev address 
}; 

class CLASS_POPUP : public CLASS_BOX 
{ 
   protected: 
      char config_position_x;          // X 
      char config_position_y;          // Y 
      char config_box_forcolor;        // FC 
      char config_box_backgroundcolor; // BC 
      char config_box_barfccolor;      // BAR FC 
      char config_box_barbgrcolor;     // BAR BC 
      char config_box_type;            // type 

      char status_select_num;          // num(sub) 
      char status_unitcount;           // unit counts 

      // unit 
      Struct_popup_unit *unit_current; // unit current 
      Struct_popup_unit *unit_begin;   // unit begin 
      Struct_popup_unit *unit_end;     // unit end 

   public: 
      // main modules 
      CLASS_POPUP(char x,char y,char fccol,char charbgrcol 
 ,char barfc,char barbgrcol,char boxtype); 
// constructor 1 
      CLASS_POPUP(void);                        // constructor 2 
      ~CLASS_POPUP(void);                       // deconstructor 
      char operation(void);                     // operation 
// select ok - TRUE 
// select fail - FALSE 

      // sub modules 
      void setinitdata(char x,char y,char fccol,char charbgrcol 
      ,char barfc,char barbgrcol,char boxtype); 

      void unit_initialize( void ); 

      void unit_append(char *string);           // append string func 
      void unit_destroy(void);                  // destroy end of unit 

      void operation_curunitput(char barstatus);// current unit put func 

      void get_selectnum(char *num);            // get select num 
}; 

CLASS_POPUP::CLASS_POPUP(char x,char y,char fccol,char bgrcol 
,char barfc,char barbgrcol,char boxtype) 
{ 
   // config field set 
   CLASS_POPUP::config_position_x = x;              // X 
   CLASS_POPUP::config_position_y = y;              // Y 
   CLASS_POPUP::config_box_forcolor = fccol;        // FC 
   CLASS_POPUP::config_box_backgroundcolor = bgrcol;// BC 
   CLASS_POPUP::config_box_barfccolor = barfc;      // BAR FC 
   CLASS_POPUP::config_box_barbgrcolor = barbgrcol; // BAR BC 
   CLASS_POPUP::config_box_type = boxtype;          // type 

   CLASS_POPUP::status_select_num = 1;              // num(sub) 
   CLASS_POPUP::status_unitcount = 0;               // unit counts 

   CLASS_POPUP::unit_initialize();                  // unit initialize 
   return; 
} 

CLASS_POPUP::CLASS_POPUP(void) 
{ 
   // config field set 
   CLASS_POPUP::config_position_x = 0;              // X 
   CLASS_POPUP::config_position_y = 0;              // Y 
   CLASS_POPUP::config_box_forcolor = 0;            // FC 
   CLASS_POPUP::config_box_backgroundcolor = 0;     // BC 
   CLASS_POPUP::config_box_barfccolor = 0;          // BAR FC 
   CLASS_POPUP::config_box_barbgrcolor = 0;         // BAR BC 
   CLASS_POPUP::config_box_type = 0;                // type 

   CLASS_POPUP::status_select_num = 1;              // num(sub) 
   CLASS_POPUP::status_unitcount = 0;               // unit counts 

   CLASS_POPUP::unit_initialize();                  // unit initialize 
   return; 
} 

CLASS_POPUP::~CLASS_POPUP(void) 
{ 
   // deconstructor 
   register int count; 
   CLASS_POPUP::unit_current = CLASS_POPUP::unit_begin; 
   for( count=0 ; count<=CLASS_POPUP::status_unitcount ; count++ ) 
   { 
      delete CLASS_POPUP::unit_current; 
      CLASS_POPUP::unit_current 
      = CLASS_POPUP::unit_current->unit_next; 
   } 
   return; 
} 

void CLASS_POPUP::setinitdata(char x,char y,char fccol,char bgrcol 
    ,char barfc,char barbgrcol,char boxtype) 
{ 
   // set initialize data 
   CLASS_POPUP::CLASS_POPUP(x,y,fccol,bgrcol,barfc,barbgrcol,boxtype); 
   return; 
} 

void CLASS_POPUP::unit_initialize( void ) 
{ 
   // initialize unit 

   // allocation unit 
   CLASS_POPUP::unit_begin = (Struct_popup_unit *) new Struct_popup_unit; 
   if( CLASS_POPUP::unit_begin != NULL ) 
   { 
      // allocation success : data setting 
      CLASS_POPUP::unit_begin->name[0] = '\0'; 
      CLASS_POPUP::unit_begin->status_unitnum = 0; 
      CLASS_POPUP::unit_begin->config_ignoreunit = 0; 
      CLASS_POPUP::unit_begin->unit_prev = CLASS_POPUP::unit_end; 

      // initialize unit_current 
      CLASS_POPUP::unit_current = CLASS_POPUP::unit_begin; 
   } 
   else 
   { 
      printf(" Memory allocaiton failured.\n"); 
      asm mov ah,1Ch; // exit 
      asm int 21h; 
   } 
   return; 
} 

void CLASS_POPUP::unit_append(char *string) 
{ 
   // append unit 
   Struct_popup_unit *unit_temp; 

   // allocation 
   unit_temp = (Struct_popup_unit *) new Struct_popup_unit; 

   if( unit_temp != NULL ) 
   { 
      // allocation success : data set 
      strcpy( unit_temp->name , string ); 
      unit_temp->status_unitnum    = ++CLASS_POPUP::status_unitcount; 
      unit_temp->config_ignoreunit = 0; 

      unit_temp->unit_next = CLASS_POPUP::unit_begin->unit_next; 

      // link - link between unit_current and unit_temp. 
      //        and change unit_current. 
      unit_temp->unit_prev = CLASS_POPUP::unit_current; 
      CLASS_POPUP::unit_current->unit_next = unit_temp; 
      CLASS_POPUP::unit_current = unit_temp; 

      // setting unit_end 
      CLASS_POPUP::unit_end = unit_temp; 
      // unit_current and unit_end is equal. 

      // begin unit link data change 
      CLASS_POPUP::unit_begin->unit_prev = CLASS_POPUP::unit_end; 
   } 
   else 
   { 
      printf(" Memory allocaiton failured.\n"); 
      asm mov ah,1Ch; // exit 
      asm int 21h; 
   } 
   return; 
} 

void CLASS_POPUP::unit_destroy(void) 
{ 
   // destroy end of unit 
   if( CLASS_POPUP::status_unitcount >= 1 ) // data exist check. 
   { 
      // destroy unit 
      CLASS_POPUP::unit_current->unit_prev->unit_next 
= CLASS_POPUP::unit_begin->unit_next; 
      CLASS_POPUP::status_unitcount--; 
      delete CLASS_POPUP::unit_current; 
      // link cut 
      CLASS_POPUP::unit_current = unit_current->unit_prev; 

      // setting unit_end 
      CLASS_POPUP::unit_end = unit_current; 

      // begin unit link data change 
      CLASS_POPUP::unit_begin->unit_prev = CLASS_POPUP::unit_end; 
   } 
   return; 
} 

void CLASS_POPUP::operation_curunitput(char barstatus) 
{ 
   // current unit put func 
   char *putstring; 
   unsigned char plusy; 

   putstring = CLASS_POPUP::unit_current->name; 

   // get plusy 
   if( CLASS_POPUP::unit_current->status_unitnum == 0 ) 
      plusy = CLASS_POPUP::unit_current->unit_prev->status_unitnum; 
   else 
      plusy = CLASS_POPUP::unit_current->status_unitnum; 

   // set color 
   if( barstatus == 1 ) // if barstatus is 1? 
     textattr( (CLASS_POPUP::config_box_barbgrcolor << 4) 
| CLASS_POPUP::config_box_barfccolor ); 
   else 
     textattr( (CLASS_POPUP::config_box_backgroundcolor << 4) 
| CLASS_POPUP::config_box_forcolor ); 

   gotoxy(CLASS_POPUP::config_position_x+1+1 
 ,CLASS_POPUP::config_position_y+plusy+1); 

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
textcolor( barstatus==0 ? CLASS_POPUP::config_box_forcolor : 
 CLASS_POPUP::config_box_barfccolor ); 
     } 
   } 
   return; 
} 

char CLASS_POPUP::operation(void) 
{ 
   // operation 
   unsigned char getkey; 
   register int count; 

   // draw box 
   CLASS_BOX::activebox( CLASS_POPUP::config_box_forcolor , 
 CLASS_POPUP::config_box_backgroundcolor , 
 CLASS_POPUP::config_position_x , 
 CLASS_POPUP::config_position_y , 
 strlen(CLASS_POPUP::unit_begin->unit_next->name)+1, 
 CLASS_POPUP::status_unitcount+2 , 
 CLASS_POPUP::config_box_type ); 

   // put units 
   CLASS_POPUP::unit_current = CLASS_POPUP::unit_begin; 
   for( count=1; count<=CLASS_POPUP::status_unitcount ; count++ ) 
   { 
      CLASS_POPUP::unit_current = CLASS_POPUP::unit_current->unit_next; 
      CLASS_POPUP::operation_curunitput(0); 
   } 

   // set position 
   CLASS_POPUP::unit_current = CLASS_POPUP::unit_begin; 
   for( count=1; count<=CLASS_POPUP::status_select_num; count++ ) 
      CLASS_POPUP::unit_current = CLASS_POPUP::unit_current->unit_next; 
   CLASS_POPUP::operation_curunitput(1); 

   while(1) 
   { 
      getkey = getch(); 
      if( getkey == 0 ) 
      { 
 getkey = getch(); 
 switch( getkey ) 
 { 
    case 72: 
      CLASS_POPUP::operation_curunitput(0); 
      if( CLASS_POPUP::unit_current->unit_prev->status_unitnum 
  == 0 ) 
 CLASS_POPUP::unit_current 
 = CLASS_POPUP::unit_current->unit_prev->unit_prev; 
      else 
 CLASS_POPUP::unit_current 
 = CLASS_POPUP::unit_current->unit_prev; 
      CLASS_POPUP::operation_curunitput(1); 
      break; 
    case 80: 
      CLASS_POPUP::operation_curunitput(0); 
      CLASS_POPUP::unit_current 
      = CLASS_POPUP::unit_current->unit_next; 
      CLASS_POPUP::operation_curunitput(1); 
      break; 
    case 75: 
    case 77: 
      CLASS_POPUP::status_select_num = unit_current->status_unitnum; 
      if( CLASS_POPUP::config_box_type & 64 ) // if pulldown? 
      { 
 // recover background 
 CLASS_BOX::recoverbackground(); 
 return getkey; 
      } 
 } 
      } 
      else 
      { 
 if( getkey == 13 ) 
 { 
    CLASS_POPUP::status_select_num = unit_current->status_unitnum; 
    CLASS_BOX::recoverbackground(); // background recover 
    return 13; 
 } 
 if( getkey == 27 ) return 27; 
      } 
   } 
} 

void CLASS_POPUP::get_selectnum(char *num) 
{ 
   *num = CLASS_POPUP::status_select_num; 
   return; 

