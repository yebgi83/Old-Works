#define M_640X480 0 
#define M_800X600 1 

static struct 
{ 
    unsigned int sizex; 
    unsigned int sizey; 
} screeninfo; // ȭ�� �ػ� ���� 

extern void setgraph( char mode ); 
