#include <math.h>
#include "sqrt.h"

// 최근 몇가지의 데이터를 보관하느냐의 크기를 결정한다. 
#define CALLIST_ARRAY_SIZE 3

typedef struct
{
    unsigned short Datas;
    unsigned long  Data[CALLIST_ARRAY_SIZE];
    unsigned long  Sum;
    unsigned long  RecentData;
}CalList;

void AddDataToCalList( CalList *plist, unsigned long data )
{  
    int c;
    
    // 숫자값을 입력한다. 
    if( plist->Datas < CALLIST_ARRAY_SIZE ) plist->Datas++;
    plist->Sum += data; 
    plist->Sum -= plist->Data[0];
    plist->RecentData = data;

    for( c = 1; c < CALLIST_ARRAY_SIZE; c++ )
       plist->Data[c - 1] = plist->Data[c];
    
    plist->Data[CALLIST_ARRAY_SIZE - 1] = data;
};

void AddDiffToCalList( CalList *plist, unsigned long data )
{
    // 편차를 입력한다. 
    AddDataToCalList( plist, data - plist->RecentData );
}

long GetAverageNorm( CalList list )
{ 
    short c;
    long diff;
    long sum_diff = 0;
    
    // 표준 편차를 구하는 함수
    for( c = 0; c < list.Datas; c++ )
    {
        // 편차를 구해서 
        if( c == 0 )
            diff = list.Data[c];
        else
            diff = list.Data[c] - list.Data[c - 1];
            
        // 제곱을 한다음, 평균을 구하기 위해 누적 시킨다. 
        diff *= diff; 
        sum_diff += diff;
    }
    // 나누기를 한다음에. 
    sum_diff /= list.Datas;
    return sum_diff;
}

short GetAverage( CalList list )
{
    return list.Sum / list.Datas;
}

double DoHSA( short data, CalList *run_list )
{
    short  i, j;
    long   run_mean;
    long   sum_diff = 0, max_sum_diff = 0, min_sum_diff = 16777817;
    double r_diff = 0;
    double s_diff = 0;
    double ret_value = 0;
    
    // 시간격을 구했다고 가정하고 
    // 1. 간격에 대한 평균값을 구하는 과정을 수행한다. 
    AddDataToCalList( run_list, data );
    run_mean = GetAverage( *run_list );
    
    // 평균값을 구했다면, 평균과의 편차를 구한다.
    for( i = 0; i < run_list->Datas; i++ )
    {
        for( j = 0; j < i; j++ )
        {
             sum_diff += (run_list->Data[i] - run_mean);
        
             // 편차중에 최대와 최소값을 구한다. 
             if( sum_diff > max_sum_diff ) max_sum_diff = sum_diff;
             if( sum_diff < min_sum_diff ) min_sum_diff = sum_diff;
        }
    } 

    // 경향선을 그려내기 위한 과정을 수행한다
    r_diff = (double)max_sum_diff - (double)min_sum_diff;

    // 이동 표준 편차를 구한다. 
    s_diff = (double)GetAverageNorm( *run_list ); 

    if( s_diff == 0 ) 
        ret_value = 1.0; 
    else 
        ret_value = r_diff * r_diff / s_diff;
    return log(ret_value);
}
