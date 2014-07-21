#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct 
{
        int num[6];
        int times;
}LottoRecord;

typedef struct
{
        int gap[5]; 
        int times;
}LottoGapRecord;

typedef struct
{
        int gap[5];
        int times;
}LottoGapSet;

#define LOTTO_RECORD_RANGE 10
#define LOTTO_GAP_RANGE    10

int LottoRecordCount = 0;
int LottoGapRecordCount = 0;
int LottoGapSetCount = 0;

LottoRecord    LR[512];
LottoGapRecord LGR[512];
LottoGapSet    LGS[512];

void ViewAllLottoRecord()
{
     int i, j;
     printf("LottoRecords.\n");
     for( i = 0 ; i < LottoRecordCount ; i++ )
     {
          printf("%d : ", i);
          for( j = 0 ; j < 6 ; j++ )
               printf("%d", LR[i].num[j]);
          printf("  %d Times\n", LR[i].times );
     }
}

void ViewAllLottoGapRecord()
{
     int i, j;
     printf("LottoGapRecords.\n");
     for( i = 0 ; i < LottoGapRecordCount ; i++ )
     {
          printf("%d : ", i);
          for( j = 0 ; j < 5 ; j++ )
               printf("%d", LGR[i].gap[j]);
          printf("  %d Times\n", LGR[i].times );
     }
     
}

void ViewAllLottoGapSet()
{
     int i, j;
     printf("LottoGapSet.\n");
     for( i = 0 ; i < LottoGapSetCount ; i++ )
     {
          printf("%d : ", i);
          for( j = 0 ; j < 5 ; j++ )
               printf("%d", LGS[i].gap[j]);
          printf("  %d Times\n", LGS[i].times );
     }
     
}

void AddLottoRecord( LottoRecord lr )
{
     lr.times = 1;
     if( LottoRecordCount == 511 ) 
         printf("LottoRecordCount : Overflow!\n");
     else
     {
         memcpy( &LR[LottoRecordCount], &lr, sizeof(lr) );
         LottoRecordCount++;
     }
}

void AddLottoGapRecord( LottoGapRecord lgr )
{
     lgr.times = 1;
     if( LottoGapRecordCount == 511 )
         printf("LottoGapRecordCount : Overflow!\n");
     else
     {
         memcpy( &LGR[LottoGapRecordCount], &lgr, sizeof(lgr) );
         LottoGapRecordCount++;
     }
}

void AddLottoGapSet( LottoGapSet lgs )
{
     lgs.times = 1;
     if( LottoGapSetCount == 511 )
         printf("LottoGapSetCount : Overflow!\n");
     else
     {
         int i, j;
         for( i = 0; i < 5; i++ )
         {
              for( j = 0; j < i; j++ )
              {
                   if( lgs.gap[i] < lgs.gap[j] )
                   {
                       int temp = lgs.gap[i];
                       lgs.gap[i] = lgs.gap[j];
                       lgs.gap[j] = temp;
                   }
              }
         }
         memcpy( &LGS[LottoGapSetCount], &lgs, sizeof(lgs) );
         LottoGapSetCount++;
     }
}

int  CompareAllLottoRecord( LottoRecord lr, int start, int end )
{
     int i, j;
     for( i = start - 1 ; i < end; i++ )
     {
          bool cond = true;
          for( j = 0 ; j < 6 ; j++ )
               cond = cond && ( LR[i].num[j] == lr.num[j] );
          if( cond == true ) return i;
     } 
     return -1;
}
 
int  CompareAllLottoGapRecord( LottoGapRecord lgr, int start, int end )
{
     int i, j;
     for( i = start - 1 ; i < end; i++ )
     {
          bool cond = true;
          for( j = 0 ; j < 5 ; j++ )
          {
               cond = cond && ( LGR[i].gap[j] == lgr.gap[j] );
          }
          if( cond == true ) return i;
     } 
     return -1;
}

int  CompareAllLottoGapSet( LottoGapSet lgs, int start, int end )
{
     int i, j;
     for( i = 0; i < 5; i++ )
     {
          for( j = 0; j < i; j++ )
          {
               if( lgs.gap[i] < lgs.gap[j] )
               {
                   int temp = lgs.gap[i];
                   lgs.gap[i] = lgs.gap[j];
                   lgs.gap[j] = temp;
               }
          }
     }

     for( i = start - 1 ; i < end; i++ )
     {
          bool cond = true;
          for( j = 0 ; j < 5 ; j++ )
          {
               cond = cond && ( LGS[i].gap[j] == lgs.gap[j] );
          }
          if( cond == true ) return i;
     } 
     return -1;
}

int  SortAllLottoRecord( void )
{
     int i, j;
     for( i = 0 ; i < LottoRecordCount ; i++ )
          for( j = 0 ; j < i ; j++ )
          {
               if( LR[i].times < LR[j].times )
               {
                   LottoRecord temp;
                   memcpy( &temp, &LR[i], sizeof(LottoRecord) );
                   memcpy( &LR[i], &LR[j], sizeof(LottoRecord) );
                   memcpy( &LR[j], &temp, sizeof(LottoRecord) );                   
               }
          }
}

int  SortAllLottoGapRecord( void )
{
     int i, j;
     for( i = 0 ; i < LottoGapRecordCount ; i++ )
          for( j = 0 ; j < i ; j++ )
          {
               if( LGR[i].times < LGR[j].times )
               {
                   LottoGapRecord temp;
                   memcpy( &temp, &LGR[i], sizeof(LottoGapRecord) );
                   memcpy( &LGR[i], &LGR[j], sizeof(LottoGapRecord) );
                   memcpy( &LGR[j], &temp, sizeof(LottoGapRecord) );                   
               }
          }
}

int  SortAllLottoGapSet( void )
{
     int i, j;
     for( i = 0 ; i < LottoGapSetCount ; i++ )
          for( j = 0 ; j < i ; j++ )
          {
               if( LGS[i].times < LGS[j].times )
               {
                   LottoGapSet temp;
                   memcpy( &temp, &LGS[i], sizeof(LottoGapSet) );
                   memcpy( &LGS[i], &LGS[j], sizeof(LottoGapSet) );
                   memcpy( &LGS[j], &temp, sizeof(LottoGapSet) );                   
               }
          }
}

void LoadLottoRecords( int start, int end )
{    
     int stage = 0;
     
     FILE *fp;
     fp = fopen( "통계.txt", "rt" );

     if( fp == NULL )
     {
         printf("로또 통계 파일이 없습니다.\n");
         return;
     }
          
     while( !feof(fp) )
     {
            int i;
            
            LottoRecord lr;
            LottoGapRecord lgr;
            LottoGapSet    lgs;
            
            stage++;
            fscanf( fp, "%d%d%d%d%d%d\n", &(lr.num[0]),
                                          &(lr.num[1]),
                                          &(lr.num[2]),
                                          &(lr.num[3]),
                                          &(lr.num[4]),
                                          &(lr.num[5]) );
            if( stage < start || stage > end ) continue;

            //for( i = 0 ; i < 6 ; i++ ) printf("%d ",lr.num[i]);
            //printf("\n");
            
            for( i = 1 ; i < 6 ; i++ ) lgr.gap[i-1] = (lr.num[i] - lr.num[i-1]) / LOTTO_GAP_RANGE;
            for( i = 1 ; i < 6 ; i++ ) lgs.gap[i-1] = (lr.num[i] - lr.num[i-1]) / LOTTO_GAP_RANGE;
            for( i = 0 ; i < 6 ; i++ ) lr.num[i] = lr.num[i] / LOTTO_RECORD_RANGE;
            
            //for( i = 0 ; i < 6 ; i++ ) printf("%d ",lr.num[i]);
            //printf("\n");
            
            //ViewAllLottoRecord();
            //system("PAUSE");
            
            i = CompareAllLottoRecord( lr, 1, LottoRecordCount );
            if( i == -1 )
                AddLottoRecord( lr ); 
            else
                LR[i].times++;

            i = CompareAllLottoGapRecord(lgr, 1, LottoGapRecordCount );
            if( i == -1 )
                AddLottoGapRecord( lgr ); 
            else
                LGR[i].times++;

            i = CompareAllLottoGapSet(lgs, 1, LottoGapSetCount );
            if( i == -1 )
                AddLottoGapSet( lgs ); 
            else
                LGS[i].times++;
     }
     
     SortAllLottoRecord();
     SortAllLottoGapRecord();
     SortAllLottoGapSet();
     
     fclose(fp);
}

int MakeNumberUsingLottoRecord( int rec_idx, int num_idx )
{
     int plus = rand() % LOTTO_RECORD_RANGE; 
     return 1 + LR[rec_idx].num[num_idx] * LOTTO_RECORD_RANGE + plus;
}

void GenerateLottoNumber( LottoRecord *plr, int pat, int level )
{
     int j, k;
     LottoRecord lr;
     LottoGapRecord lg;
     LottoGapSet ls;
     
     printf("pat [%d %d]", pat, LottoRecordCount - pat );
     for( j = 0; j < 6; j++ )
          printf("%d ", LR[ LottoRecordCount - pat].num[j] );
     printf("\n");

     while(1)
     {
          while(1)
          {
                  bool loop = false;

                  for( j = 0; j < 6; j++ )
                       lr.num[j] = MakeNumberUsingLottoRecord( LottoRecordCount - pat, j );
               
                  for( j = 0; j < 6; j++ )
                  {
                       for( k = 0; k < 6; k++ )
                            if( j != k && lr.num[j] == lr.num[k] ) 
                            {
                                loop = true;
                                break;
                            }
                  } 
                  
                  int max = 0;
                  for( j = 0; j < 6; j++ )
                       if( lr.num[j] > max ) max = lr.num[j];
                  if( max > 45 ) loop = true;
                  
                  if( loop == false ) break; 
          }
        
          for( j = 0; j < 6; j++ )
          {
               for( int k = 0; k < j; k++ )
                    if( lr.num[j] < lr.num[k] )
                    {
                        int temp = lr.num[j];
                        lr.num[j] = lr.num[k];
                        lr.num[k] = temp;
                    }
          }
          
          for( j = 1 ; j < 6 ; j++ ) lg.gap[j-1] = (lr.num[j] - lr.num[j-1]) / LOTTO_GAP_RANGE;
          for( j = 1 ; j < 6 ; j++ ) ls.gap[j-1] = (lr.num[j] - lr.num[j-1]) / LOTTO_GAP_RANGE;

          printf("Num ");          
          for( j = 0 ; j < 6 ; j++ ) printf("%3d ", lr.num[j]);
          printf("\n");         

          printf("Gap ");          
          for( j = 0 ; j < 5 ; j++ ) printf("%3d ", ls.gap[j]);
          printf("\n");          

          if( level == 0 ) j = CompareAllLottoGapSet(ls, LottoGapSetCount - 4, LottoGapSetCount );
          if( level == 1 ) j = CompareAllLottoGapRecord(lg, LottoGapRecordCount - 4, LottoGapRecordCount );
          
          if( level == 0 && j != -1 ) if( LGS[j].times <= 1 ) j = -1;
          if( level == 1 && j != -1 ) if( LGR[j].times <= 1 ) j = -1;
          
          if( j != -1 ) break;
     }
     
     for( j = 0 ; j < 6 ; j++ ) plr->num[j] = lr.num[j];
}

void GenerateLottoNumberWithException( LottoRecord *plr )
{
     int j, k;
     LottoRecord lr;
     LottoGapRecord lg;
     LottoGapSet ls;
     
     while(1)
     {
          while(1)
          {
                  bool loop = false;

                  for( j = 0; j < 6; j++ )
                       lr.num[j] = 1 + rand() % 45; 
               
                  for( j = 0; j < 6; j++ )
                  {
                       for( k = 0; k < 6; k++ )
                            if( j != k && lr.num[j] == lr.num[k] ) 
                            {
                                loop = true;
                                break;
                            }
                  } 
                  
                  int max = 0;
                  for( j = 0; j < 6; j++ )
                       if( lr.num[j] > max ) max = lr.num[j];
                  if( max > 45 ) loop = true;
                  
                  if( loop == false ) break; 
          }
        
          for( j = 0; j < 6; j++ )
          {
               for( int k = 0; k < j; k++ )
                    if( lr.num[j] < lr.num[k] )
                    {
                        int temp = lr.num[j];
                        lr.num[j] = lr.num[k];
                        lr.num[k] = temp;
                    }
          }
          
          for( j = 1 ; j < 6 ; j++ ) lg.gap[j-1] = (lr.num[j] - lr.num[j-1]) / LOTTO_GAP_RANGE;
          for( j = 1 ; j < 6 ; j++ ) ls.gap[j-1] = (lr.num[j] - lr.num[j-1]) / LOTTO_GAP_RANGE;

          printf("Num ");          
          for( j = 0 ; j < 6 ; j++ ) printf("%3d ", lr.num[j]);
          printf("\n");         

          printf("Gap ");          
          for( j = 0 ; j < 5 ; j++ ) printf("%3d ", ls.gap[j]);
          printf("\n");          

          j = CompareAllLottoRecord( lr, 1, LottoRecordCount );
          
          if( j == -1 ) break;
     }
     
     for( j = 0 ; j < 6 ; j++ ) plr->num[j] = lr.num[j];
}

int main(int argc, char *argv[])
{
     int i, j;
     LottoRecord lr[10];
          
     LoadLottoRecords( 1, 429 );

     for( i = 0; i < 6; i++ ) 
     {
          Sleep(100);          
          srand( (unsigned int) GetTickCount() );
          GenerateLottoNumber( &lr[i], 1 + i, 0 );
     }
          
     Sleep(100);          
     srand( (unsigned int) GetTickCount() );
     GenerateLottoNumberWithException( &lr[6] );
     
     system("cls");

     printf("Random Lotto Number\n");
     for( i = 0; i < 7; i++ )
     {
          for( j = 0; j < 6; j++ )
               printf("%3d ", lr[i].num[j]);
          printf("\n");
     }

     FILE *fp = fopen("기록.txt", "at");
     
     //fprintf(fp, "---------------------------------------------\n");
     for( i = 0; i < 7; i++ )
     {
          for( j = 0; j < 6; j++ )
               fprintf(fp, "%3d ", lr[i].num[j]);
          fprintf(fp, "\n");
     }
     fclose(fp);
      
     system("PAUSE");
     return EXIT_SUCCESS;
}
