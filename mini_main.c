//main.c
#include <lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "KPM.h"
#include "interrupt.h"
#include "delay.h"
#include "buzzer.h"
s32 hour,min,sec,date,month,year,day;
int main()
{
     RTC_Init();// Initialize RTC hardware
		 InitLCD();// Initialize LCD display
     InitKPM(); // Initialize keypad 
	   buzzer_init(); // Initialize buzzer 
     interrupt_init();// Initialize external interrupts
     SetRTCTimeInfo(10,40,0);// Set initial time
     SetRTCDateInfo(23,03,2026);// Set initial date
     SetRTCDay(1);// Set day of week 
     while(1)
     {
			      // Read current time from RTC
            GetRTCTimeInfo(&hour,&min,&sec);
			      // Display time on LCD 
            DisplayRTCTime(hour,min,sec);
			      // Read current date from RTC
            GetRTCDateInfo(&date,&month,&year);
			      // Display date on LCD
            DisplayRTCDate(date,month,year);
			      // Read current day
            GetRTCDay(&day);
			      // Display day
            DisplayRTCDay(day);
			      // Check if medicine time matches current time
            check_med();// If match ? buzzer ON + alert message
     }
}
