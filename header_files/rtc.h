#include "types.h"

/* RTC time variables */
extern u32 rhour;
extern u32 rmin;
extern u32 rsec;

/* RTC date variables */
extern u32 rdate;
extern u32 rmonth;
extern u32 ryear;

/* RTC function declarations */
void Init_RTC(void);
void RTC_GetTime(void);
void RTC_GetDate(void);
void RTC_SetTime(void);
void RTC_Set_Date(void);
void Set_RTC(void);

