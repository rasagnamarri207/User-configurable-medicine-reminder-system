//kpm.c
#include "types.h"
#include "defines.h"
#include <lpc21xx.h>
#include "kpm_defines.h"
#include "lcd.h"
u8 kpmLUT[4][4]={{'7','8','9','/'},
									{'4','5','6','*'},
									{'1','2','3','-'},
									{'C','0','=','+'}};
// Initialize Keypad
void InitKPM(void)
{
	WNIBBLE(IODIR1,ROW0,15);
}
// Scan columns to detect key press
u32 ColScan(void)
{
	return((RNIBBLE(IOPIN1,COL0)<15)?0:1);
}
// Identify which row key is pressed
u32 RowCheck(void)
{
	u32 rno;
	for(rno=0; rno<4; rno++)
	{
		WNIBBLE(IOPIN1,ROW0,~(1<<rno));
		if(ColScan()==0)
		{
			break;
		}
	}
	//make rows as default
	WNIBBLE(IOPIN1,ROW0,0x0);
	return rno;
}
// Identify which column key is pressed
u32 ColCheck(void)
{
	u32 cno;
	for(cno=0; cno<4; cno++)
	{
		if(RBIT(IOPIN1,(COL0+cno))==0)
		{
			break;
		}
	}
	return cno;
}

u32 KeyScan(void)
{
	u32 rno,cno,keyv;
	//wait for switch press
	while(ColScan());
	//find the row_no
	rno=RowCheck();
	//find the col_no
	cno=ColCheck();
	//get the key value using kpmLUT
	keyv=kpmLUT[rno][cno];
	//wait for switch release
	while(!ColScan());
	return keyv;
}
// Function to read multi-digit number from keypad
u32 ReadNum(void)
{
	u8 key;
	u32 sum=0,digit=0;
	while(1)
	{
	  key=KeyScan();
		if(key>='0'&&key<='9')
		{
			CharLCD(key);
			sum=(sum*10)+(key-'0');
			digit++;
		}
		// '=' key ? end of input
		else if(key=='=')
		{
			break;
		}
		// '*' key ? backspace (delete last digit)
		else if(key=='*')
		{
			if(digit>0)
			{
			sum=sum/10; // Remove last digit
			CmdLCD(0x10);// Move cursor left
			StrLCD(" ");
			CmdLCD(0x10);
			digit--;// Decrease digit count
		}
	}
}
	return sum;
}
