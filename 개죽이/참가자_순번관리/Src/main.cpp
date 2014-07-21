#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    short num;
	FILE *fp = fopen("../참가자.dat", "rb+"); 
	
	if( fp == NULL )
	{
        printf("참가자 파일이 없습니다.\n");
		printf("참가자 파일의 위치는 현재 폴더의 상위 폴더여야 합니다.\n");
        return EXIT_SUCCESS;
	} 
	
	fread( &num, 2, 1, fp );
	printf("현재 누적순번은 %d입니다.\n", num );
	printf("새로운 누적순번을 정하세요. ( 0 = 취소 ) : " );
	scanf("%d", &num);
	
	if( num == 0 ) 
	    printf("취소 되었습니다.\n"); 
	else
	{
	 	fseek( fp, 0, SEEK_SET );
	    fwrite( &num, 2, 1, fp );
	    printf("누적 순번을 변환했습니다.\n"); 
    }
    fclose(fp);
  	return EXIT_SUCCESS;
}
