//mp_rtc_defines.h

#define FOSC 12000000
#define CCLK (5*FOSC)    
#define PCLK (CCLK/4)

#define PREINT_VAL (int) ((PCLK / 32768) - 1)
#define PREFRAC_VAL (PCLK -((PREINT_VAL + 1) * 32768))

#define RTC_ENABLE (1<<0)

#define RTC_RESET (1<<1)
#define buzzer 0
#define sw1 1
#define sw2 3

#define RTC_CLKSRC (1<<4)
#define EINT0_VIC_CHNO 14
#define EINT0_INPUT_PIN 0x0000000C
#define EINT1_VIC_CHNO 15
#define EINT1_INPUT_PIN 0x000000C0

#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
