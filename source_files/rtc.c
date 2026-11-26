#include <LPC214x.h>
#include "types.h"
#include "rtc.h"
#include"delay.h"
#include"minikpm.h"

/* LCD and keypad functions from other files */
extern void CmdLCD(unsigned char cmd);
extern void strLCD(char *str);
extern unsigned int Get_Number(unsigned int);

/* RTC variables */
u32 rhour, rmin, rsec;
u32 rdate, rmonth, ryear;

/* Initialize RTC */
void Init_RTC(void)
{
    CCR = 0x00;

    /* Prescaler values for 15 MHz peripheral clock */
    PREINT  = 457;
    PREFRAC = 8896;

    /* Enable RTC and select RTC clock source */
    CCR = 0x01 | (1 << 4);
}

/* Read time from RTC */
void RTC_GetTime()
{
    rhour = HOUR;
    rmin  = MIN;
    rsec  = SEC;
}

/* Read date from RTC */
void RTC_GetDate(void)
{
    rdate  = DOM;
    rmonth = MONTH;
    ryear  = YEAR;
}

/* Write time to RTC */
void RTC_SetTime(void)
{
    CCR = 0x00;

    HOUR = rhour;
    MIN  = rmin;
    SEC  = rsec;

    CCR = 0x01 | (1 << 4);
}

/* Write date to RTC */
void RTC_Set_Date(void)
{
    CCR = 0x00;

    DOM   = rdate;
    MONTH = rmonth;
    YEAR  = ryear;

    CCR = 0x01 | (1 << 4);
}

/* Get and validate date and time */
void Set_RTC(void)
{
//menu
u32 mkey,Tkey,Dkey;
u32 flag=0;
while(1)
{
menu :CmdLCD(0x01);
	strLCD("MENU");
	CmdLCD(0x01);
	strLCD("1:TIME 2:DATE");
	CmdLCD(0xC0);
	strLCD("3:EXIT");
	mkey=KeyScan();
	delay_ms(500);
	if(mkey=='1')
	{
		//flag=1;
	TIME_MENU:CmdLCD(0x01);
		strLCD("1:HH 2:MIN 3:SEC");
		CmdLCD(0xC0);
	    strLCD("4:BACK 5:EX");
		Tkey=KeyScan();
		delay_ms(200);
		//if(mkey=='5')
		//	goto menu;
		if(Tkey=='1')
		{
			flag=1;
			HOUR_INPUT:
    			CmdLCD(0x01);
    			strLCD("Enter Hour:");
    			rhour = Get_Number(2);
					if (rhour > 23)
    					{
        					CmdLCD(0x01);
        					strLCD("Invalid Hour");
							delay_ms(500);
        					goto HOUR_INPUT;
    					}
		}
		if(Tkey=='2')
		{
				flag=1;
				MIN_INPUT:
			    	CmdLCD(0x01);
    				strLCD("Enter Minute:");
    				rmin = Get_Number(2);

    				if (rmin > 59)
    				{
        				CmdLCD(0x01);
        				strLCD("Invalid Minute");
						delay_ms(500);
        				goto MIN_INPUT;
    				}
		}
		if(Tkey=='3')
		{		 
				flag=1;
				SEC_INPUT:
				    CmdLCD(0x01);
    				strLCD("Enter Second:");

    				rsec = Get_Number(2);

    					if (rsec > 59)
    					{
        					CmdLCD(0x01);
        					strLCD("Invalid Second");
							delay_ms(500);
        					goto SEC_INPUT;
    					}
		}
		
		if(Tkey=='4')
			goto menu;
		if(Tkey>'5')
		{
			CmdLCD(0x01);
			strLCD("INVALID KEY");
			delay_ms(500);
			goto TIME_MENU;
		}
		RTC_SetTime();
		if(flag==1)
		{
			CmdLCD(0x01);
		 	strLCD("TIME UPDATED");
			delay_ms(500);
		}
		if(Tkey=='5')
			break;
		if(mkey!='3')
			goto TIME_MENU;		
	 }
	 if(mkey=='2')
	 {
	 	//flag=1;
	 	DATE_MENU:CmdLCD(0x01);
			strLCD("1:DD 2:MM 3:YY");
			CmdLCD(0xC0);
	    	strLCD("4:BACK 5:EX");
			Dkey=KeyScan();
			delay_ms(200);
			if(Dkey=='1')
			{
				flag=1;
				// Enter date first 
				DATE_INPUT:
    				CmdLCD(0x01);
    				strLCD("Enter Date:");
    				rdate = Get_Number(2);

    				if (rdate < 1 || rdate > 31)
    				{
        				CmdLCD(0x01);
        				strLCD("Invalid Date");
						delay_ms(500);
        				goto DATE_INPUT;
    				}
			}

			if(Dkey=='2')
			{
				flag=1;
				// Enter month next 
				MONTH_INPUT:
    				CmdLCD(0x01);
    				strLCD("Enter Month:");
    				rmonth = Get_Number(2);

    					if (rmonth < 1 || rmonth > 12)
    					{
        					CmdLCD(0x01);
        					strLCD("Invalid Month");
							delay_ms(500);
        					goto MONTH_INPUT;
    					}

    					// February: accept dates 1 to 28 
    					if (rmonth == 2)
						{
   					 		if (rdate > 28)
        					{
            					CmdLCD(0x01);
            					strLCD("Invalid Date");
								delay_ms(500);
            					goto DATE_INPUT;
        					}
    					}
    		      	// Months having 30 days 
    				if (rmonth == 4 || rmonth == 6 ||
        				rmonth == 9 || rmonth == 11)
    				{
        				if (rdate > 30)
        				{
            				CmdLCD(0x01);
            				strLCD("Invalid Date");
							delay_ms(500);
            				goto DATE_INPUT;
        				}
    				}
			}
			if(Dkey=='3')
			{
				flag=1;
				// Enter year 
				YEAR_INPUT:
    				CmdLCD(0x01);
    				strLCD("Enter Year:");
    				ryear = Get_Number(4);

    				if (ryear < 2000 || ryear > 2099)
    				{
        				CmdLCD(0x01);
        				strLCD("Invalid Year");
						delay_ms(500);
        				goto YEAR_INPUT;
    				}
			 }
		if(Dkey=='4')
			goto menu;
		if(Dkey>'5')
		{
			CmdLCD(0x01);
			strLCD("INVALID KEY");
			delay_ms(500);
			goto DATE_MENU;
		}
		RTC_Set_Date();
		if(flag==1)
		{
			CmdLCD(0x01);
			strLCD("DATE UPDATED");
			delay_ms(500);
		}
		if(Dkey=='5')
			break;
		if(mkey!='3')
			goto DATE_MENU;
		else
			break;
	}

if(mkey=='3')
		break;
if(flag==1)
{
	CmdLCD(0X01);
	strLCD("RTC UPDATED");
	delay_ms(500);
}
if(mkey>'3')
{
	CmdLCD(0x01);
	strLCD("INVALID KEY");
	delay_ms(500);
	goto menu;
}
}
}

		


/*
// Enter date first 
DATE_INPUT:
    CmdLCD(0x01);
    strLCD("Enter Date:");
    rdate = Get_Number(2);

    if (rdate < 1 || rdate > 31)
    {
        CmdLCD(0x01);
        strLCD("Invalid Date");
        goto DATE_INPUT;
    }

// Enter month next 
MONTH_INPUT:
    CmdLCD(0x01);
    strLCD("Enter Month:");
    rmonth = Get_Number(2);

    if (rmonth < 1 || rmonth > 12)
    {
        CmdLCD(0x01);
        strLCD("Invalid Month");
        goto MONTH_INPUT;
    }

    // February: accept dates 1 to 28 
    if (rmonth == 2)
    {
        if (rdate > 28)
        {
            CmdLCD(0x01);
            strLCD("Invalid Date");
            goto DATE_INPUT;
        }
    }

    // Months having 30 days 
    if (rmonth == 4 || rmonth == 6 ||
        rmonth == 9 || rmonth == 11)
    {
        if (rdate > 30)
        {
            CmdLCD(0x01);
            strLCD("Invalid Date");
            goto DATE_INPUT;
        }
    }

// Enter year 
YEAR_INPUT:
    CmdLCD(0x01);
    strLCD("Enter Year:");
    ryear = Get_Number(4);

    if (ryear < 2000 || ryear > 2099)
    {
        CmdLCD(0x01);
        strLCD("Invalid Year");
        goto YEAR_INPUT;
    }

// Enter hour 
HOUR_INPUT:
    CmdLCD(0x01);
    strLCD("Enter Hour:");
    rhour = Get_Number(2);

    if (rhour > 23)
    {
        CmdLCD(0x01);
        strLCD("Invalid Hour");
        goto HOUR_INPUT;
    }

// Enter minute 
MIN_INPUT:
    CmdLCD(0x01);
    strLCD("Enter Minute:");
    rmin = Get_Number(2);

    if (rmin > 59)
    {
        CmdLCD(0x01);
        strLCD("Invalid Minute");
        goto MIN_INPUT;
    }

// Enter second 
SEC_INPUT:
    CmdLCD(0x01);
    strLCD("Enter Second:");

    rsec = Get_Number(2);

    if (rsec > 59)
    {
        CmdLCD(0x01);
        strLCD("Invalid Second");
        goto SEC_INPUT;
    }
	
// Update RTC registers 
    RTC_SetTime();
    RTC_Set_Date();

    CmdLCD(0x01);
    strLCD("RTC Updated");
}	*/
