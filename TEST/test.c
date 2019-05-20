#include "reg51.h"
sbit BEEP=P1^3;
void delay(int i)
{
	  while(i--);
}
void main()
{
	  P0=0;
	while(1)
	{
	  BEEP=!BEEP;
	   delay(200);
	}
}