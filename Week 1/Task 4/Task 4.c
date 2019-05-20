#include<reg52.h>
#include<math.h>
typedef unsigned int ui;
sbit led0=P2^0;
sbit led1=P2^1;
sbit led2=P2^2;
sbit led3=P2^3;
sbit led4=P2^4;
sbit led5=P2^5;
sbit led6=P2^6;
sbit led7=P2^7;



int f(int i)
{
   int n=0;
	
	while(8-i>0) n=pow(2,i)+n,i++;
	return n;
	
}


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

//main function
void main()
{
	  int i,j,aw;
	for(j=8;i>=0;j--)
	{
      if(j==0) break;
	    for(i=0;i<j;i++)
	   {
     aw=f(j)+pow(2,i);
			 aw=~aw;
			 P2=aw;
     delay(1e4);
			
	   }

	 }
    P2=~0;
	
	while(1);
	  
}