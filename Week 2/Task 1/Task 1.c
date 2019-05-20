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
char code we[][3]={0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,1,1,0,1,0,1,1,1,1,1};
	char code du[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	                                     0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};


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
	 
	
while(1)
{
			       LSA=we[2][0],LSB=we[2][1],LSC=we[2][2];
	  P0=du[6];
	delay(500);
	P0=0;
			 			 LSA=we[5][0],LSB=we[5][1],LSC=we[5][2];
	  P0=du[6];
	delay(500);
		P0=0;
			 			 LSA=we[8][0],LSB=we[8][1],LSC=we[8][2];
	  P0=du[6];
		delay(500);
		P0=0;
}
		 
}