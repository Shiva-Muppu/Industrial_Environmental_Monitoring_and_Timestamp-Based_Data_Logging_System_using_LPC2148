#include<lpc21xx.h>
#include "miniadc.h"
void read_lm35(float *tdegc,float *tdegf)
{
	unsigned short int dval;
	int flag;
	float eAR;
	if(flag==0)
	{
	Init_ADC();
	flag=1;
	}
	 Read_ADC(2,&dval,&eAR);
	*tdegc=(eAR*100);
	*tdegf=(*tdegc*(9/5)+32);
}
void read_lm35np(float *tdegc,float *tdegf)
{
	unsigned short int dval1,dval2;
	float eAR1,eAR2;
	static int flag;
	if(flag==0)
	{
		Init_ADC();
		flag=1;
	}
	Read_ADC(0,&dval1,&eAR1);
	Read_ADC(1,&dval2,&eAR2);
	*tdegc=((eAR1-eAR2)*100);
	*tdegf=(*tdegc*(9/5)+32);
}
