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

	char code du[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	                                     0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

 void delay(unsigned int i)   //i=1 10us
{
	while(i--);
}

void we(char i)   //λѡ0~7
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

void see(int i,char j)
{
	   we(j);
	    i=i/pow(10,j);
	   P0=i%10;
  
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



static i=0,t=0;      //static   
//main function
void main()
{
	 we(0);
   P0=du[0];
	 timer0();

	 while(t<12);
	EA=0;
	P0=0;
	 while(1);
}
void exit() interrupt 1
{
	 	TH0=0XFC;
	TL0=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		t++;
	}
	if(t<10)
	{
	we(0);
	P0=du[t];
	}
	else
	{
		we(0);
		P0=du[0];
		delay(500);
		P0=0;
		we(1);
		P0=du[1];
		delay(500);
		P0=0;
	}
	
}
	