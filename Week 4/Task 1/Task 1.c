#include "reg52.h"		

typedef unsigned int ui;	 
typedef unsigned char uc;



bit DIR;

ui count,value,t;


void timer1()
{
	TMOD|=0X10;

	TH1 = 0xff; 
	TL1 = 0xff;   //1us
		
	ET1=1;
	EA=1;
	TR1=1;
}
ui   t=0;
void main()
{	
	timer1(); 
	while(1)
	{
		if(count>100)							
		{  
			count=0;
			if(DIR==1)					 
			{
			  value++;
			}			
			if(DIR==0)
			{
			  value--;
			}
				
		}

		if(value==1000)
		{
		  DIR=0;
		}
		if(value==0)
		{
		  DIR=1;
		}	

		if(t>1000)  //1000*1us
		{
			t=0;
		}
		if(t <value)	
		{
			P2=0xff;
		}
		else
		{
			P2=0;
		}		
	}		
}

void ee(void) interrupt 3  
{
	TH1 = 0xff; 
	TL1 = 0xff;   //1us
	t++; 
    count++;
	
}