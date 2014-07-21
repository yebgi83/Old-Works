typedef struct
{
    char Filename[256];
    char Flag_ForGame;
    long Size;
    short OptimizeNum;
}WAVUnit;

WAVUnit *pWAVList;

void InitWAVList( void )
{
     pWAVList = new WAVUnit [1396];
}

void RemoveWAVList( void )
{
     if( pWAVList != NULL )
     {
         delete pWAVList;
         pWAVList = NULL;
     }
}
  
void RegisterWAVUnit( int n, char filename[256], long size )
{
     if( pWAVList != NULL )
     {
         // �����̸��� ����ϰ� 
         strcpy( pWAVList[n].Filename, filename );
         
         // ũ�� �Է� 
         pWAVList[n].Size = size;
         
         // ���ӿ��ֿ� ���� ���� Ȯ�ο� 0��� ǥ��
         pWAVList[n].Flag_ForGame = 0;
         
     } 
}    

void SetUsedForGame( int n ) 
{
     pWAVList[n].Flag_ForGame = 1;
}

void ViewWAVList( void )
{
     int c, num = 0;
     long needsize = 0;
     for( c = 0; c < 1396; c++ )
     {
         if( pWAVList[c].Flag_ForGame == 1 ) 
         {
             num++;
             needsize += pWAVList[c].Size;
             printf("<%d> = %d : %s ( Total %d Bytes )\n", num, c, pWAVList[c].Filename, needsize );
         }
     }
}

void NoteOptimize( BMS *pbms )
{
     FILE *fp = fopen("test.txt", "wt");
     
     int num = 0;
     int c, c2;
     
     // ����ȭ�Ǵ� ��ȣ�� ���Ѵ�. 
     for( c = 0; c < 1396; c++ )
     {
         if( pWAVList[c].Flag_ForGame == 1 ) 
         {
             pWAVList[c].OptimizeNum = num;
             num++;
         }
     }
     
     for( c = 0; c < (pbms->Note).nDatas; c++ )
     {
         printf("%d:", c);
         for( c2 = 14; c2 <= 19; c2++ )
         {
             printf( "%3d ", pWAVList[ BMS_NOTE( pbms, c2 - 10, c ) ].OptimizeNum );
         }
         printf( "\n" );
     }
     fclose(fp);        
}
