//buzzer.c
#include <lpc21xx.h>
#include "mp_rtc_defines.h"
#include "rtc.h"
void buzzer_init(void)
{
    IODIR0 |= 1<<buzzer;
}

void buzzer_on(void)
{
    IOSET0 =1<<buzzer;
}

void buzzer_off(void)
{
    IOCLR0 =1<<buzzer;
}
