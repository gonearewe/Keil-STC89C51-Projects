#include"stdhead.h"
 void delay(unsigned int i)   //i=1 10us
{
	while(i--);
}


void we(char i)   //0~7
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
ui th1,tl1,th0,tl0;
void timer0(ui t)    //      t  ms
{
	TMOD=0X01;
	th0=(65536-1000*t)/256;
	tl0=(65536-1000*t)%256;
	TH0=th0;
	TL0=tl0;
	ET0=1;
	EA=1;
	TR0=1;	
}

void timer1(ui t)      //  t    ms
{
   TMOD=0X01;
	th1=(65536-1000*t)/256;
	tl1=(65536-1000*t)%256;
	TH1=th1;
	TL1=tl1;
	ET0=1;
	EA=1;
	TR0=1;	
}

void uart ()     	//4800
{
   TMOD=0x20;
	PCON=0X80;			
	TH1=0XF3;			
	TL1=0XF3;
	 TR1=1;
	 SCON=0x50;
	 EA=1;
	 ES=1;
}
void display(uc j,ui t)     // j   we,  t    num
{
	char n[8],i,m=1;
	for(i=0;i<j;i++)
	{
		n[i]=t%10;
		t=t/10;
	}
	for(i=j;i>0;i--)
	{ 
		if(n[i]==0)   n[i]=16;
		if(	n[i-1]!=0)   break;
	}
	for(i=j-1;i>=0;i--)
	{
	   P0=0;
		we(i);
		m=n[i];
		P0=du[m];
		delay(100);
		}
}

int key()       //key()
{
	char a=0;
	P1=0x0f;
	if(P1!=0x0f)
	{
		delay(1000);
		if(P1!=0x0f)
		{	
			P1=0X0F;
			switch(P1)
			{
				case(0X07):	keynum=0;break;
				case(0X0b):	keynum=1;break;
				case(0X0d): keynum=2;break;
				case(0X0e):	keynum=3;break;
			}
			
			P1=0XF0;
			switch(P1)
			{
				case(0X70):	 keynum=keynum;break;
				case(0Xb0): keynum=keynum+4;break;
				case(0Xd0):  keynum=keynum+8;break;
				case(0Xe0):	keynum=keynum+12;break;
			}
			while((a<50)&&(P1!=0xf0))	 
			{
				delay(1000);
				a++;
			}	
		  return keynum;
			 
		}
		else return -1;
	}
    else return -1;
		}