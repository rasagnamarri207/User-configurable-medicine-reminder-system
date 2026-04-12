//rtc_defines.h
#define FOSC 12000000
#define CCLK (5*FOSC)    
#define PCLK (CCLK/4)

#define PREINT_VAL (int) ((PCLK / 32768) - 1)
#define PREFRAC_VAL (PCLK -((PREINT_VAL + 1) * 32768))
// Bit 0 ? Clock Enable --> 1 = Enable RTC counters  0 = Disable RTC counters
#define RTC_ENABLE (1<<0)

// Bit 1 ? Clock Reset --> 1 = Reset RTC counters    0 = Normal operation
#define RTC_RESET (1<<1)
#define RTC_CLKSRC (1<<4) 

#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
