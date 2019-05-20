#include<reg52.h>
sbit led0=P2^0;
sbit led1=P2^1;
sbit led2=P2^2;
sbit led3=P2^3;
sbit led4=P2^4;
sbit led5=P2^5;
sbit led6=P2^6;
sbit led7=P2^7;
void delay(unsigned int i)
{
	while(i--);
}
void main()
{
	delay(1e8);
	led0=0;
	delay(1e8);
	led1=0;
	delay(1e8);
	led2=0;
	delay(1e8);
	led3=0;
	delay(1e8);
	led4=0;
	delay(1e8);
	led5=0;
	delay(1e8);
	led6=0;
	delay(1e8);
	led7=0;
	delay(1e8);
	led7=1;
	led6=1;
	led5=1;
	led4=1;
	led3=1;
	led2=1;
	led1=1;
	led0=1;
	
}