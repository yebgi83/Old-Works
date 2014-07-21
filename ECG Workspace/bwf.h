#ifndef BWF_H

#define BWF_H
#define MAX_BUTTERWORTH_ORDER           5	   // 버터워스 필터 최대 차수		

/* Butter Worth 필터 구조체 */
typedef struct 
{
   char   order;
   double num[MAX_BUTTERWORTH_ORDER];
   double den[MAX_BUTTERWORTH_ORDER];
   double inbuf[MAX_BUTTERWORTH_ORDER];
   double outbuf[MAX_BUTTERWORTH_ORDER];
}BWF;

double ButterWorth( BWF *pfilter, int input )
{
    double result;
	char order = pfilter->order;
	char end_array_idx = pfilter->order - 1;
	char in, out;
	
	// 버퍼에 데이터를 누적한다.
	for( in = 1; in < order; in++ )
	   pfilter->inbuf[ in - 1 ] = pfilter->inbuf[ in ];
	pfilter->inbuf[end_array_idx] = input;
	
	result = 0.0;
	for( in = 0; in < order; in++ )
	   	result += ( pfilter->num[in] * pfilter->inbuf[ end_array_idx - in ] );
	
	for( out = 0; out < order - 1; out++ )
	   	result -= ( pfilter->den[1 + out] * pfilter->outbuf[ end_array_idx - out ] );
    
	for( out = 1; out < order; out++ )
	   pfilter->outbuf[ out - 1 ] = pfilter->outbuf[ out ];
 	
	pfilter->outbuf[end_array_idx] = result;
	return (double)result;
}
#endif
