#include <cstdlib>
#include <iostream>

#include <conio.h>

using namespace std;

int V[4] = { 5, 10, 14, 16 };
int H[4] = { 18,  9,  9, 9 };

int _V[4] = { 0, 0, 0, 0 };
int _H[4] = { 0, 0, 0, 0 };

int C[4][4] = 
{
    1, 1, 0, 1,
    0, 1, 1, 0,
    0, 1, 0, 1,
    1, 0, 1, 1, 
};

int N[4][4] = 
{
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

int I[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

void Debug(void)
{
     int x, y;
     printf("\n");
     for( y = 0; y < 5; y++ )
     {
          if( y < 4 )
          {
              for( x = 0; x < 4; x++ )
                   printf("%4d\t", N[y][x]);
              printf("%4d\n", _H[y]);
          }
          else
          {
              for( x = 0; x < 4; x++ )
                   printf("%4d\t", _V[x]);
              printf("\n");
          }
     }
}

void Debug2(void)
{
     int c;
     static int n = 0;
     n++;
     printf("%5d : ", n);
     for( c = 0; c < 10; c++ )
         printf("[%d]",I[c]);
     printf("\n");
} 

void Swap( int *a, int *b )
{
     int c = *a;
     *a = *b;
     *b = c;
}

int Sol(void)
{
     int x, y;
     int c, s;
     
     s = 0;
     for( c = 0; c < 4; c++ )
     {
          if( V[c] == _V[c] ) s++;
          if( H[c] == _H[c] ) s++;
     }
     return s;
}

void Put( int x, int y, int t )
{
     N[y][x] = I[t];
}

void Attempt(void)
{
     int x, y, t = 0;
     static int atm = 0;
     
     for( y = 0; y < 4; y++ )
     {
          for( x = 0; x < 4; x++ )
               if( C[y][x] == 1 ) 
               {
                   t++;
                   Put( x, y, t );
               }
     }
     
     _V[0] = N[0][0] + N[1][0] + N[2][0] + N[3][0];
     _V[1] = N[0][1] + N[1][1] + N[2][1] + N[3][1];
     _V[2] = N[0][2] + N[1][2] + N[2][2] + N[3][2];
     _V[3] = N[0][3] + N[1][3] + N[2][3] + N[3][3];
     _H[0] = N[0][0] + N[0][1] + N[0][2] + N[0][3];
     _H[1] = N[1][0] + N[1][1] + N[1][2] + N[1][3];
     _H[2] = N[2][0] + N[2][1] + N[2][2] + N[2][3];
     _H[3] = N[3][0] + N[3][1] + N[3][2] + N[3][3];

     
     atm++;
     if( atm % 1000 == 0 ) 
     {
         Debug2();
         printf("%d Attempt.\n", atm);
         Debug();
         printf("Match number = %d\n", Sol() );
     }    

     
     if( Sol() == 8 )
     {
         Debug();
         printf("Solution!\n");
         getch();
     }
}

void Perm( int i, int n )
{
     int j;
     
     if( i == n ) 
     {
         Attempt();
         return;
     }
     
     for( j = i; j < n; j++ )
     {
          Swap( &I[i], &I[j] ); 
          Perm( i + 1, n );
          Swap( &I[i], &I[j] ); 
     }

     return;
}

int main(int argc, char *argv[])
{
     Perm(0, 10);
     system("PAUSE");
     return EXIT_SUCCESS;
}

