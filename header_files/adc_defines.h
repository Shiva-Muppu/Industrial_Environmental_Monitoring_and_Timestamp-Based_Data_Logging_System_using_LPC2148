//adc_defines.h

#define FOSC 12000000//crystal oscillator clock
#define CCLK (FOSC*5)//cpu clock freq
#define PCLK (CCLK/4)//peripheral clk freq
#define ADC_CLK 3000000	

//defines for ADCR sfr
#define CLKDIV_BITS        8//8-15
#define PDN_BIT            21
#define ADC_CONV_START_BIT 24
#define CLKDIV_VAL ((PCLK/ADC_CLK)-1)

//defines for ADDR sfr
#define DIGITAL_DATA_BITS  6 //6-15
#define DONE_BIT           31

#define AIN0_FUNC 0x00400000
#define AIN1_FUNC 0x01400000
#define AIN2_FUNC 0x04400000
#define AIN3_FUNC 0x00000000
