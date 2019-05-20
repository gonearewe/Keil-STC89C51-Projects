#include<reg52.h>
typedef unsigned int ui;
sbit led0=P2^0;
sbit led1=P2^1;
sbit led2=P2^2;
sbit led3=P2^3;
sbit led4=P2^4;
sbit led5=P2^5;
sbit led6=P2^6;
sbit led7=P2^7;
static ui  j=0,m=0;
void timer0()    
{
	TMOD=0X01;
	TH0=0XFC;
	TL0=0X18;	     // 1ms
	ET0=1;
	EA=1;
	TR0=1;	
}
void delay(unsigned int i)   //i=1 10us
{
	while(i--);
}
void main()
{
   
	timer0();

		P2=0;
		while(m<40);
	 EA=0;
	P2=~0;
	while(1);
		
	}
	
	void exit1() interrupt 1
	{
		 ui n;
			TH0=0XFC;
	    TL0=0X18;	
	  	j++;
		if(j==100)
		{
		  	j=0;
 	      if(m==0) delay(1e7),n=0x01;
				m++;
			if(m%5==0)
			{
			n=0x01<<(m/5);
		  
			}
			P2=n;
		}
		
	}
	
	
