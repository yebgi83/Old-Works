typedef struct Struct_editbox_unit 
{ 
   unsigned int column;// column number 
   char linedata[128]; // linedata 
   Struct_editbox_unit *unit_prev; // prev link 
   Struct_editbox_unit *unit_next; // next link 
}; 

class CLASS_EDITBOX : private CLASS_BOX 
{ 
   protected: 
      char *config_filename;  // filename 
      char config_position_x; // x of editbox 
      char config_position_y; // y of editbox 
      char config_size_x;     // xsize of editbox 
      char config_size_y;     // ysize of editbox 
      unsigned int config_edit_row;    // row 
      unsigned int config_edit_column; // column 
      unsigned int config_edit_beginputcolumn; // begin put column 
      unsigned int config_columncount; // columncount 
      Struct_editbox_unit *editline_current; 
      Struct_editbox_unit *editline_home; 
      Struct_editbox_unit *editline_end; 
   public: 
      CLASS_EDITBOX( void );     // constructor 

      void filename_set( unsigned char *filename ); 
      void show_maximum( void ); // show the edit box 

      void line_create( void ); 

      void putcurrentline( char y_inbox ); // put current line 
      void putcurrentline_setcolor( char *checkstr ); 
      // check string and set color. 

      void operation( void ); 
}; 

void CLASS_EDITBOX::CLASS_EDITBOX( void ) 
{ 
    // initialize 
    CLASS_EDITBOX::config_columncount = 0; 

//     CLASS_EDITBOX::line_create(); 
    CLASS_EDITBOX::editline_home = CLASS_EDITBOX::editline_current; 
    return; 
} 

void CLASS_EDITBOX::putcurrentline( char y_inbox ) 
{ 
    gotoxy( CLASS_EDITBOX::config_position_x+1+1 
   ,CLASS_EDITBOX::config_position_y+1+y_inbox+1); 
    cprintf("MOV AX,CX"); 
    return; 
} 

void CLASS_EDITBOX::filename_set( unsigned char *filename ) 
{ 
    strcpy( CLASS_EDITBOX::config_filename , filename ); 
    return; 
} 

void CLASS_EDITBOX::show_maximum(void) 
{ 
    register int count; 
    CLASS_BOX::activebox(15,1,0,1,80,23,1); 
    CLASS_EDITBOX::config_position_x = 0; 
    CLASS_EDITBOX::config_position_y = 1; 
    CLASS_EDITBOX::config_size_x = 80; 
    CLASS_EDITBOX::config_size_y = 23; 
    gotoxy( CLASS_EDITBOX::config_position_x+1+2 
   ,CLASS_EDITBOX::config_position_y+1); 
    cprintf(" %s : none                        ",CLASS_EDITBOX::config_filename); 
    return; 
} 

void CLASS_EDITBOX::line_create( void ) 
{ 
    // create line 
    Struct_editbox_unit *editline_temp = new Struct_editbox_unit; 

    if( editline_temp != NULL) 
    { 
editline_temp->linedata[0] = '\0'; 

// link 
editline_temp->unit_prev = CLASS_EDITBOX::editline_current; 
CLASS_EDITBOX::editline_current->unit_next = editline_temp; 

// setting column 
editline_temp->column = CLASS_EDITBOX::editline_current->column+1; 

// set end line 
CLASS_EDITBOX::editline_end = editline_temp; 

CLASS_EDITBOX::config_columncount++; 
    } 
    return; 
} 

void CLASS_EDITBOX::operation( void ) 
{ 
    register int count; 
    Struct_editbox_unit *editline_temp; 
    editline_temp = CLASS_EDITBOX::editline_home; 
    for( count=1 ; count<=CLASS_EDITBOX::config_columncount ; count++ ) 
    { 
// CLASS_EDITBOX::putcurrentline( count-1 ); 
editline_temp = editline_temp->unit_next; 
    } 
    return; 
} 
