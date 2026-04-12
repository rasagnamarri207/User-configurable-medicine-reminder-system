//interrupt.h
#include "types.h"

void interrupt_init(void);
void EINT0_ISR(void) __irq;
void EINT1_ISR(void) __irq;
void check_med(void);

//extern volatile int flag0;
//extern volatile int flag1;
u32 atoi(u8*);
void menu(void);
void editRTC(void);
void editHour(s32 *hour);
void editMin(s32 *min);
void editSec(s32 *sec);
void editDate(s32 *date);
void editMonth(s32 *month);
void editYear(s32 *year);
void editDay(s32 *day);

void medicineTimeEdit(void);
void editM1_time(void);
void editM2_time(void);
void editM3_time(void);
