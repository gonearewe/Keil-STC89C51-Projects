#include<reg52.h>
#include<math.h>
typedef unsigned int ui;
typedef unsigned char uc;
sbit led0=P2^0;
sbit led1=P2^1;
sbit led2=P2^2;
sbit led3=P2^3;
sbit led4=P2^4;
sbit led5=P2^5;
sbit led6=P2^6;
sbit led7=P2^7;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

	char code du[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	                                     0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0};

void we(char i)   //??0~7
{
	switch(i)
	{
		case 0:LSA=0,LSB=0,LSC=0;break;
		case 1:LSA=1,LSB=0,LSC=0;break;
		case 2:LSA=0,LSB=1,LSC=0;break;
		case 3:LSA=1,LSB=1,LSC=0;break;
		case 4:LSA=0,LSB=0,LSC=1;break;
		case 5:LSA=1,LSB=0,LSC=1;break;
		case 6:LSA=0,LSB=1,LSC=1;break;
		case 7:LSA=1,LSB=1,LSC=1;
	}
}

delay(unsigned int i)
{
   while(i--);
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

void display(int t)
{
	char n[2],i,m=1;
	for(i=0;i<2;i++)
	{
		n[i]=t%10;
		t=t/10;
	}
		for(i=1;i>0;i--)
	{ 
		if(n[i]==0)   n[i]=16;
		if(	n[i-1]!=0)   break;
	}
	for(i=1;i>=0;i--)
	{
	   P0=0;
		we(i);
		m=n[i];
		P0=du[m];
		delay(1000);
	}
}
char t=10;
int h=0;
void main()
{
     timer0();
		 while(1)
		 {
		 while(t>=0)  
		 {
		      display(t);
					led7=0;
		 }
		 t=2;
		 while(t>=0)
		 {
		    P2=0xa3;
				delay(1000);
				P2=0xe3;
				delay(1000);
			}
			t=10;
			while(t>=0)
			{
			display(t);
			led5=0;
			}
	 }
}

void exit()  interrupt 1
{
     	TH0=0XFC;
	    TL0=0X18;	
			h++;
			if(h==1000)  t--,h=0;
			
}