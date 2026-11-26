#include<lpc21xx.h>
#include"types.h"
#define EINT0_PIN_FUNC 0x000000C0
extern volatile unsigned char set_time_flag;
void eint0_isr(void) __irq;
unsigned int count;
void init_eint()
{
	PINSEL0&=(u32)~3<<6;
	PINSEL0|=EINT0_PIN_FUNC;
	//VICIntSelect=0  its already in 0 by default
	VICIntEnable=1<<15;//14 - channel number
	VICVectCntl0=(1<<5)|15;//(1<<5)for vicvectcnt register to enable
	VICVectAddr0=(u32)eint0_isr;
	//EXTINT=0;//SET TO TRIGGER MODE
	EXTMODE=1<<1;//enablng edge triggering
	//EXTPOLAR=1<<1;//enabling falling edge triggering
	//IODIR1=1<<16;//LED PIN; TO RISE INTERRUPT
}
void eint0_isr(void) __irq
{
	//IOPIN1^=1<<16;
	set_time_flag=1;
	EXTINT=1<<1;
	VICVectAddr=0;
}
