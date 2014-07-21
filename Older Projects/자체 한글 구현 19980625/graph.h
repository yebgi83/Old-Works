#define M_640X480 0 
#define M_800X600 1 

static struct 
{ 
    unsigned int sizex; 
    unsigned int sizey; 
} screeninfo; // 화면 해상도 정보 

extern void setgraph( char mode ); 
