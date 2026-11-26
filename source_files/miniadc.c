#include<lpc21xx.h>
#include"types.h"
#include"delay.h"
#include"adc_defines.h"
void Init_ADC()
{
	PINSEL1&=~(0x3<<((29-16)*2));
	PINSEL1|=AIN2_FUNC;//|AIN1_FUNC|AIN2_FUNC|AIN3_FUNC;
	ADCR|=(1<<PDN_BIT)|(CLKDIV_VAL<<CLKDIV_BITS);
}
void Read_ADC(u8 chNO,u16 *dVal,f32*eAR)
{
	ADCR&=0xFFFF00;
	ADCR|=(1<<ADC_CONV_START_BIT)|(1<<chNO);
	delay_us(3);
	while(((ADDR>>DONE_BIT)&1)==0);
	ADCR&=~(1<<ADC_CONV_START_BIT);
	*dVal=((ADDR>>DIGITAL_DATA_BITS)&1023);
	*eAR=*dVal*(3.3/1023);
}
