int StringToNumber( char *str )
{
    int value = 1;
    int result = 0;
    for( int c = strlen(str) - 1; c >= 0; c-- )
    {
        int idx = 0;
        if( str[c] >= '0' && str[c] <= '9' ) 
        {
            idx = str[c] - '0';
            result += (value * idx);
        }
        value *= 10;
    }
    return result;
}

int HexToNumber( char upper, char lower )
{
    char *hexstr = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int upper_idx = (int)(strchr( hexstr, upper ) - hexstr);
    int lower_idx = (int)(strchr( hexstr, lower ) - hexstr);
    if( upper_idx < 0 || lower_idx < 0 ) return -1; else return 36 * upper_idx + 1 * lower_idx;
}

int DecToNumber( char upper, char middle, char lower )
{
    return 100 * (upper - '0') + 10 * (middle - '0') + 1 * (lower - '0');
}

#include "wave.h"
#include "img.h"
#include "mix.h"

