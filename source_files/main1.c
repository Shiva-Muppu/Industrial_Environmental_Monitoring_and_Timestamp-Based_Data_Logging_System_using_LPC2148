#include <lpc21xx.h>
#include "types.h"
#include "miniadc.h"
#include "lm35.h"
#include "rtc.h"
#include "minilcd.h"
#include "minikpm.h"
#include "uart.h"
#include "interrupt.h"
#include"delay.h"
//#include"uart_rtc_transmit.h"

#define BUZZER_PIN (1 << 19)
#define SET_TEMP   50
unsigned int prev_sec = 60;
volatile unsigned char set_time_flag = 0;
float tdegc, tdegf;
unsigned int temp;
int main(void)
{
  unsigned int temp;
   float tdegc, tdegf;

	unsigned int prev_min = 0;

    Init_ADC();
    Init_RTC();
    InitLCD();
    InitKPM();
    UART0_Init();
    init_eint();
	UART0_Init();
	U0_TxStr("\r\n");
	U0_TxStr("============================================================\r\n");
	U0_TxStr("       INDUSTRIAL ENVIRONMENT MONITORING SYSTEM\r\n");
	U0_TxStr("          ARM7 LPC2148 | REAL-TIME DATA LOGGER\r\n");
	U0_TxStr("============================================================\r\n");
	U0_TxStr("\r\n");
	//CmdLCD(0x01);
	//strLCD("T:set point");
	//CmdLCD(0xC0);
	//set_temp = Get_Temp(5);
	CmdLCD(0x01); 

	U0_TxStr(" SYSTEM CONFIGURATION\r\n");
	U0_TxStr(" ------------------------------------------------------------\r\n");
	//U0_TxStr(" Temperature Setpoint : ");
	//U0_TxF32(set_temp,1);
	//U0_TxStr(" ");
	//UART0_Tx(0xB0);
    //U0_TxStr(" C\r\n");
	U0_TxStr(" Monitoring Status    : ACTIVE\r\n"); 
	U0_TxStr(" ------------------------------------------------------------\r\n");
	delay_ms(1000);
    IODIR0 |= BUZZER_PIN;
    IOCLR0 = BUZZER_PIN;

    while (1)
    {
        read_lm35(&tdegc, &tdegf);

        RTC_GetTime();
        RTC_GetDate();


        if (set_time_flag == 1)
        {	
			U0_TxStr("============================================================\r\n");
            U0_TxStr("\r\n");
            U0_TxStr("Time: ");

            if (rhour < 10)
                U0_TxStr("0");
            U0_TxU32(rhour);
            U0_TxStr(":");

            if (rmin < 10)
                U0_TxStr("0");
            U0_TxU32(rmin);
            U0_TxStr(":");

            if (rsec < 10)
                U0_TxStr("0");
            U0_TxU32(rsec);

			U0_TxStr(" | ");
			U0_TxStr("INTERUPPT RAISED....");
			delay_ms(500);
            set_time_flag = 0;
            Set_RTC();

            RTC_GetTime();
            RTC_GetDate();
			CmdLCD(0x01);
            prev_sec = 60;
            U0_TxStr("\r\n");
			U0_TxStr("Time : ");

            if (rhour < 10)
                U0_TxStr("0");
            U0_TxU32(rhour);
            U0_TxStr(":");

            if (rmin < 10)
                U0_TxStr("0");
            U0_TxU32(rmin);
            U0_TxStr(":");

            if (rsec < 10)
                U0_TxStr("0");
            U0_TxU32(rsec);

			U0_TxStr(" | ");
			U0_TxStr("RTC UPDATED");
			U0_TxStr("\r\n");
			U0_TxStr("============================================================\r\n");
			U0_TxStr("SYSTEM STATUS : MONITORING ACTIVE ");
			U0_TxStr("\r\n");
			U0_TxStr("============================================================\r\n");
        }

        temp = (unsigned int)tdegc;

        // LCD temperature display 
		//CmdLCD(0X01);
		CmdLCD(0x80);
		//strLCD("D:");
        U32LCD(rdate);
        strLCD("/");
        U32LCD(rmonth);
        strLCD("/");
        U32LCD(ryear);

        //CmdLCD(0x80);
		CmdLCD(0xC0);
		//strLCD("T:");
        CharLCD((rhour / 10) + '0');
        CharLCD((rhour % 10) + '0');
        CharLCD(':');

        CharLCD((rmin / 10) + '0');
        CharLCD((rmin % 10) + '0');
        CharLCD(':');

        CharLCD((rsec / 10) + '0');
        CharLCD((rsec % 10) + '0');

		strLCD("  ");
        strLCD("TM:");
        U32LCD(temp);
		CharLCD(223);
        strLCD("C");

        
		 //U0_TxStr("RTC LOOP\r\n");

        //Buzzer alert
		//CUSTOM TEMO FOR BUZZER 
        if (tdegc > SET_TEMP)
		{
			CmdLCD (0x01);
			strLCD("BUZZER ALERT!!");
			//CmdLCD (0x01);
			delay_ms(1000);
			CmdLCD(0X01);
			U0_TxStr("\r\n");
			U0_TxStr(" [!!] TEMPERATURE ALERT\r\n");
			U0_TxStr(" ------------------------------------------------------------\r\n");
			U0_TxStr(" Alert Temperature : ");
            U0_TxF32(tdegc, 1);
			U0_TxStr(" ");
			UART0_Tx(0xB0);
            U0_TxStr(" C\r\n");	
			U0_TxStr(" BUZZER STATUS : ACTIVATED\r\n");
			U0_TxStr(" ------------------------------------------------------------\r\n");		
            IOSET0 = BUZZER_PIN;
		}
        else
            IOCLR0 = BUZZER_PIN;

        // Send one record when time changes 
         //if(rsec != prev_sec )
		 /*||
            rdate != prev_date ||
            rmonth != prev_month ||
            ryear != prev_year)	*/
			if(rsec==0&&(rmin!=prev_min))
			{
			U0_TxStr("\r\n");
			U0_TxStr(" REAL-TIME SENSOR DATA\r\n");
			U0_TxStr(" ------------------------------------------------------------\r\n");
			U0_TxStr(" DATE         TIME          TEMPERATURE\r\n");
			U0_TxStr(" ------------------------------------------------------------\r\n");
            U0_TxU32(rdate);
            U0_TxStr("/");
            U0_TxU32(rmonth);
            U0_TxStr("/");
            U0_TxU32(ryear);

			U0_TxStr("    ");
            if (rhour < 10)
                U0_TxStr("0");
            U0_TxU32(rhour);
            U0_TxStr(":");

            if (rmin < 10)
                U0_TxStr("0");
            U0_TxU32(rmin);
            U0_TxStr(":");

            if (rsec < 10)
                U0_TxStr("0");
            U0_TxU32(rsec);
				
 			U0_TxStr("       ");
            U0_TxF32(tdegc, 1);
			U0_TxStr(" ");
			UART0_Tx(0xB0);
            U0_TxStr(" C\r\n");//*/
			//uart_rtc_transmit();

            prev_sec = rsec;
			prev_min=rmin;
           // prev_date = rdate;
            //prev_month = rmonth;
          //  prev_year = ryear;
        }
    }	
}
