#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define ADC_CLK 3000000

#define CLKDIV_BITS  8
#define PDN_BIT      21
#define ADC_CONV_START_BIT 24
#define CLKDIV_VAL ((PCLK/ADC_CLK)-1)

#define DIGITAL_DATA_BITA 6
#define DONE_BIT          31

#define AIN0_FUNC 0x00400000
#define AIN1_FUNC 0x01400000
#define AIN2_FUNC 0x04400000
#define AIN3_FUNC 0x00000000