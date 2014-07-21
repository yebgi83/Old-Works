#include <stdio.h>
 #include <conio.h>
 #include <string.h>

 

/*���� �˰� �ִ� �˰����� �ſ� �����߾��� �� �� ����� ����ϸ� �ڵ嵵 �����ϰ�

    �Ǵ±��� ���п� ������ �߽��ϴ�.  ��ó ���� ���ߴ� ���� �˰������� �����˴ϴ�.*/

 

/* �߰���  �κ�  */

/* ������ �κ�  */


 void SWAP( char* des, char* src ){ 
  char tmp = *des; 
  printf("%c %c\n",*des,*src);
//  *des = *src; 
//  *src = tmp; 
 } 

 void perm( char* list, int i, int n ){ 

  /* index�� permutation�� ��� ���� ����ϴ� ī���� */
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


      /*   ���� ������ �����Ϸ��� C++����� reference �� �̿��Ͽ����մϴ�  �׷��� 

      C������ ���� ������ pass by value�� �ǹǷ� ����Ÿ�� ��ȯ�� �̷�� �����ʽ��ϴ�. 
      C���� �ε��� i(start index)�� �ε���j�� ����Ÿ ��ġ�� ��ȯ�Ϸ��� �Ʒ��� ����

      pass by reference �ϱ� ���Ͽ�  pointer�� �Ķ��Ÿ�� pass �մϴ�     */ 

      SWAP( &list[i], &list[j] ); 

      /* ����Լ� ȣ�� */
      perm(list, i+1, n ); 

      /* �ռ� ��ȯ�� �ε���i(start index)�� �ε���j�� ����Ÿ ��ġ�� ������ ��ġ��ȯ�� ���Ͽ� 

          ���� ��ġ�� ���ͽ�ŵ�ϴ�.*/ 
      SWAP( &list[i], &list[j] ); 

 

      /* ù��° ���ڰ� �ٲ� ������  ������ �� ���ϴ�. */
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

 �Ʒ��� list�� "abcd"��� ���ڿ��� �̷���� ��  list�� ������ ���� ���ڿ���  

 perm �̶�� ����Լ��� �̿��Ͽ� �����ϰ� �� ����� ���ڿ��� ����մϴ�. 

*/

 
 char* list = "abcdefghi"; 

 int main(){ 
 
  int N = strlen(list);

  long  F = factorial( N );

 

  printf( "\n���ڿ� \'%s\'�� �����ϴ� ����� ���� %d!(=%ld)�Դϴ�.\n", list,  N, F  );
  printf( "�� ��� ���� �Ʒ��� �����ϴ�.\n\n");

  perm( list, 0, N-1 ); 


  getch(); 
  return 0;
} 

