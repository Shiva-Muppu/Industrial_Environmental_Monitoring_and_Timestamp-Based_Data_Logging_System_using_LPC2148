//KPM.c
#include "types.h"
#include<lpc21xx.h>
#include"types.h"
#include"minikpm_defines.h"
#include"minilcd.h"
#include "delay.h"
u32 kpmLUT[4][4]={  {'1','2','3','A'},
					{'4','5','6','B'},
					{'7','8','9','C'},
					{'*','0','#','D'}};

void InitKPM(void)
{
	IODIR1|=15<<ROW0;
}
u32 ColScan(void)
{
	if(((IOPIN1>>COL0)&15)<15)
		return 0;
	else
		return 1;
}
u32 RowCheck(void)
{
	u32 rno;
	for(rno=0; rno<4; rno++)
	{
		IOPIN1=(IOPIN1&~(15<<ROW0))|((~(1<<rno))<<ROW0);
		if(ColScan()==0)
		break;
	}
	
	IOCLR1=15<<ROW0;
	return rno;
}
u32 ColCheck(void)
{
	u32 cno;
	for(cno=0; cno<4; cno++)
	{
		if(((IOPIN1>>(COL0+cno))&1)==0)
			break;
	}
	return cno;
}



u32 KeyScan(void)
{
	u32 rno, cno,key;
	//wait for switch press
	while(ColScan());
	//find the rno
	rno=RowCheck();
	//find the cno
	cno=ColCheck();
	//get the value from LUT
	key=kpmLUT[rno][cno];
	//wait for switch release
	while(!ColScan());
	delay_ms(200);
	return key;
}
u32 ReadNum(void)
{
	u8 key;
	u32 sum=0;
	while(1)
	{
		key=KeyScan();
		if(key>='0' && key<='9')
		{
			sum=(sum*10)+(key-48);
		}
		else
			break;
	}
	return sum;
}
unsigned int Get_Number(unsigned int digits)
{
    unsigned int num = 0;
    unsigned int count = 0;
    unsigned int key;

    while (1)
    {
        key = KeyScan();
		delay_ms(200);
        if (key == '#')
        {
            if (count == digits)
                return num;
        }
        else if (key >= '0' && key <= '9')
        {
            if (count < digits)
            {
                num = (num * 10) + (key - '0');
                count++;

                CharLCD(key);
            }
        }
		if((key=='*')&&(num>0))
		{
			num=num/10;
			CmdLCD(0x10);
			CharLCD(' ');
			CmdLCD(0X10);
			count--;
		}

    }
}


unsigned int Get_Temp(unsigned int digits)
{
    unsigned int num = 0;
    unsigned int count = 0;
    unsigned int key;

    while (1)
    {
        key = KeyScan();
		delay_ms(200);
        if (key == '#')
        {
            if (count >1)
                return num;
        }
        else if (key >= '0' && key <= '9')
        {
            if (count < digits)
            {
                num = (num * 10) + (key - '0');
                count++;

                CharLCD(key);
            }
        }
		if((key=='*')&&(num>0))
		{
			num=num/10;
			CmdLCD(0x10);
			CharLCD(' ');
			CmdLCD(0X10);
			count--;
		}

    }
}
