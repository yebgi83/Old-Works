#include <cstdlib>
#include <iostream>
#include <fstream>

#define  TRUE     1
#define  FALSE   -1

using namespace std;

#include <stdio.h>
#include <conio.h>
//#include <windows.h>

#include "bwf.h"
#include "data.h"
#include "callist.h"
#include "outscr.h"

// 입력 받을 데이터 
InData IN;

BWF ECG_Filter = {
3,
{
0.256814290086484,
0.000000000000000,
-0.256814290086484,
}
,
{
1.000000000000000,
-1.357468253694337,
0.486371419827032,
}
,
{ 0, }
,
{ 0, }
};

CalList RunList;

void Test( void )
{
    short        c;
    short        trend;
    long         value;
    long         diff;
    double       exponent;
    static short  cosecu_trend = 0;
    static short  before_trend = 0;
    static short  idle_count   = 0;
    static long   period = 0;
    static long   before_diff = 0;
    static long   before_value = 0;
    static double before_exp  = 0;
    for( c = 0; c < SIZE(IN); c++ )
    {
        period++;
        
        // 필터링 처리  
        value = (short)ButterWorth( &ECG_Filter, DATA(IN, c) );
        diff  = value - before_value;

//        if( idle_count == 0 )
        {
            if( diff * before_diff < 0 )
            {
                // HSA 알고리즘 이용하여 지수 구함 
                exponent = DoHSA( period, &RunList );
                {
                    trend = (exponent - before_exp) >= 0.0 ? 1 : -1; // 경향 
                    if( before_trend == trend ) 
                        cosecu_trend++;
                    else
                        cosecu_trend = 1;
                    
                    printf( "%d : %3.10f %d %d\n", c, exponent, trend, cosecu_trend );
                    
                    idle_count = period / 3;
                    before_trend = trend; // 경향 
                }
                period = 0;
            }
        }
//        else
//            idle_count--;
        
        if( c % 1000 == 0 ) getch();

        before_exp = exponent;
        before_trend = trend;
        before_value = value;
        before_diff = diff;
    }
}

int main(int argc, char *argv[])
{ 
    IN.Used = FALSE;
    LoadInput( &IN, "ecg1.txt" );
    Test();
    system("PAUSE");
    return EXIT_SUCCESS;
}
