#include <stdhead.h>
sbit mov=P3^6;
sbit sto=P3^5;
sbit ser=P3^4;
void main()
	{

	 uc t;
  while(1)  
	{
		P2=0xfe<<t;
		delay(1000);
		t++;
		if(t==9) t=1;
	}
}