#include <math.h>
#include "sqrt.h"

// �ֱ� ����� �����͸� �����ϴ����� ũ�⸦ �����Ѵ�. 
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
    
    // ���ڰ��� �Է��Ѵ�. 
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
    // ������ �Է��Ѵ�. 
    AddDataToCalList( plist, data - plist->RecentData );
}

long GetAverageNorm( CalList list )
{ 
    short c;
    long diff;
    long sum_diff = 0;
    
    // ǥ�� ������ ���ϴ� �Լ�
    for( c = 0; c < list.Datas; c++ )
    {
        // ������ ���ؼ� 
        if( c == 0 )
            diff = list.Data[c];
        else
            diff = list.Data[c] - list.Data[c - 1];
            
        // ������ �Ѵ���, ����� ���ϱ� ���� ���� ��Ų��. 
        diff *= diff; 
        sum_diff += diff;
    }
    // �����⸦ �Ѵ�����. 
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
    
    // �ð����� ���ߴٰ� �����ϰ� 
    // 1. ���ݿ� ���� ��հ��� ���ϴ� ������ �����Ѵ�. 
    AddDataToCalList( run_list, data );
    run_mean = GetAverage( *run_list );
    
    // ��հ��� ���ߴٸ�, ��հ��� ������ ���Ѵ�.
    for( i = 0; i < run_list->Datas; i++ )
    {
        for( j = 0; j < i; j++ )
        {
             sum_diff += (run_list->Data[i] - run_mean);
        
             // �����߿� �ִ�� �ּҰ��� ���Ѵ�. 
             if( sum_diff > max_sum_diff ) max_sum_diff = sum_diff;
             if( sum_diff < min_sum_diff ) min_sum_diff = sum_diff;
        }
    } 

    // ���⼱�� �׷����� ���� ������ �����Ѵ�
    r_diff = (double)max_sum_diff - (double)min_sum_diff;

    // �̵� ǥ�� ������ ���Ѵ�. 
    s_diff = (double)GetAverageNorm( *run_list ); 

    if( s_diff == 0 ) 
        ret_value = 1.0; 
    else 
        ret_value = r_diff * r_diff / s_diff;
    return log(ret_value);
}
