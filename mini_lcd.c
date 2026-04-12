//mini_LCD.c
#include<lpc21xx.h>
#include "LCD_defines.h"
#include "types.h"
#include "defines.h"
#include "delay.h"
void WriteLCD(u8 data)
{
	SCLRBIT(IOCLR0,RW);//RW=0, write operation
	WBYTE(IOPIN0,LCD_DATA,data);
	SSETBIT(IOSET0,EN);//EN=1
	delay_us(1);
	SCLRBIT(IOCLR0,EN);//EN=0
	delay_ms(2);//internal process
}
// Send command to LCD
void CmdLCD(u8 cmd)
{
	SCLRBIT(IOCLR0,RS);//RS=0, command reg selected
	WriteLCD(cmd);
}
// Send character (data) to LCD
void CharLCD(u8 ascii)
{
	SSETBIT(IOSET0,RS);//RS=1, data reg selected
	WriteLCD(ascii);
}
// Initialize LCD
void InitLCD(void)
{
	WBYTE(IODIR0,LCD_DATA,255); //P0.8 to P0.15 as outputs
	SETBIT(IODIR0,RS);//p0.16 as output
	SETBIT(IODIR0,RW);//p0.17 as output
	SETBIT(IODIR0,EN);//p0.18 as output
	
	delay_ms(15);
	CmdLCD(MODE_8BIT_1LINE);
	delay_ms(5);
	CmdLCD(MODE_8BIT_1LINE);
	delay_us(100);
	CmdLCD(MODE_8BIT_1LINE);
	
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DISP_ON);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
}
// Display string on LCD
void StrLCD(s8* p)
{
	while(*p)
	CharLCD(*p++);
}
// Display unsigned 32-bit integer
void U32LCD(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n)// Extract digits
		{
			a[i++]=(n%10)+48;// Convert digit to ASCII
			n/=10; // Remove last digit
		}
		// Print digits in reverse order
		for(--i;i>=0;i--)
		CharLCD(a[i]);
	}
}
// Display signed 32-bit integer
void S32LCD(s32 n)
{
	if(n<0)
	{
		CharLCD('-');
		n=-n;
		U32LCD(n);
	}
}
// Display floating point number
void F32LCD(f32 fnum, u8 nDP)
{
	u32 n;
	s32 i;
	if(fnum<0)
	{
		CharLCD('-');
	}
		n=fnum;
		U32LCD(n);
		CharLCD('.');
	// Display fractional part
		for(i=0; i<nDP; i++)
		{
			fnum=(fnum-n)*10;
			n=fnum;
			CharLCD(n+48);
		}
}
// Display hexadecimal value
void HEXLCD(u32 n)
{
	u8 a[8],rem;
	s32 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n)
		{
			rem =n%16;  // Get remainder
			// Convert to ASCII (0–9 or A–F)
			(rem<10)?(rem+=48):(rem+=55);
			a[i++]=rem;
			n/=16;
		}
		for(--i; i>=0; i--)
		{
			CharLCD(a[i]);
		}
	}
}
// Display binary value
void BinLCD(u32 n, u8 nbd)
{
	s32 i;
	for(i=(nbd-1); i>=0; i--)
	{
		CharLCD(((n>>i)&1)+48);
	}
}
// Create custom character in LCD CGRAM
void BuildCGRAM(u8* p, u8 nb)
{
	s32 i;
	CmdLCD(GOTO_CGRAM);
	for(i=0; i<=nb; i++)
	{
		CharLCD(p[i]);
	}
	CmdLCD(GOTO_LINE1_POS0);
}
