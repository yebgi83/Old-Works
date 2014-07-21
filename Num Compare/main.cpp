#include <stdio.h>
 #include <conio.h>
 #include <string.h>

 

/*제가 알고 있던 알고리즘은 매우 복잡했었는 데 이 방법을 사용하면 코드도 간단하게

    되는군요 덕분에 공부좀 했습니다.  미처 알지 못했던 좋은 알고리즘으로 생각됩니다.*/

 

/* 추가한  부분  */

/* 수정한 부분  */


 void SWAP( char* des, char* src ){ 
  char tmp = *des; 
  printf("%c %c\n",*des,*src);
//  *des = *src; 
//  *src = tmp; 
 } 

 void perm( char* list, int i, int n ){ 

  /* index는 permutation의 경우 수를 계수하는 카운터 */
  static int index  = 1;  
  int j; 

  if( i == n ){ 
     printf( "%3d: ", index++ ); 

     for( j = 0; j <= n; j++ ) 
      printf( "%c", list[j] ); 
     printf( "\n" ); 
     return;
  } 
  
  {
     for( j = i; j <= n; j++ ){ 
      /* SWAP( list[i], list[j] );  */


      /*   위의 문장이 성립하려면 C++언어의 reference 를 이용하여야합니다  그러나 

      C언어에서는 위의 문장은 pass by value가 되므로 데이타의 교환이 이루어 지지않습니다. 
      C언어에서 인덱스 i(start index)와 인덱스j의 데이타 위치를 교환하려면 아래와 같이

      pass by reference 하기 위하여  pointer를 파라메타로 pass 합니다     */ 

      SWAP( &list[i], &list[j] ); 

      /* 재귀함수 호출 */
      perm(list, i+1, n ); 

      /* 앞서 교환된 인덱스i(start index)와 인덱스j의 데이타 위치를 다음의 위치교환을 위하여 

          원래 위치로 복귀시킵니다.*/ 
      SWAP( &list[i], &list[j] ); 

 

      /* 첫번째 문자가 바뀔 때마다  라인을 더 띄웁니다. */
      if( i == 0 ) 
       printf( "\n" ); 
    } 
  } 
 } 
 

 long factorial( long n ){

  if ( n  <= 1L )
   return 1L; 

 else 


  return ( n * factorial(n - 1));

 }

 

 /*

 아래는 list가 "abcd"라는 문자열로 이루어질 때  list의 순열에 따른 문자열을  

 perm 이라는 재귀함수를 이용하여 생성하고 그 경우의 문자열을 출력합니다. 

*/

 
 char* list = "abcdefghi"; 

 int main(){ 
 
  int N = strlen(list);

  long  F = factorial( N );

 

  printf( "\n문자열 \'%s\'을 나열하는 경우의 수는 %d!(=%ld)입니다.\n", list,  N, F  );
  printf( "그 모든 경우는 아래와 같습니다.\n\n");

  perm( list, 0, N-1 ); 


  getch(); 
  return 0;
} 

