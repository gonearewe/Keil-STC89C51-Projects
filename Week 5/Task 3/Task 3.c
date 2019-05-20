#include <reg52.h>
#include <math.h>
#include <intrins.h>
#define stop while(1);        //stop   for   debug
typedef unsigned int ui;
typedef unsigned char uc;
sbit A=P1^0;
sbit k3=P3^2;
sbit k4=P3^3;
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
sbit beep=P1^5;
uc  code du[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	                                     0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0};
uc  code beat[8]={0xe,0xc,0xd,0x9,0xb,0x3,0x7,0x6};
 void delay(unsigned int i)   //i=1 10us
{
	while(i--);
}

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
ui th1,tl1;
void timer0(ui t)    //    t      t  ms
{
	TMOD=0X01;
	TH0=(65536-1000*t)/256;
	TL0=(65536-1000*t)%256;
	ET0=1;
	EA=1;
	TR0=1;	
}

void timer1(ui t)      //  t    ms
{
    ui k;
		k=11059200/12;
		k=(k*t)/1000;
		k=65536-k+12;         //12     for    compensation
		th1=(uc)(k>>8);
		tl1=(uc)k;
		TMOD=1;
		TH1=th1;
		TL1=tl1;
		ET1=1;
		TR1=1;
		EA=1;
}

void uart ()
{
   TMOD=0x20;
	PCON=0X80;			//波特率加倍
	TH1=0XF3;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF3;
	 TR1=1;
	 SCON=0x50;
	 EA=1;
	 ES=1;
}
void display(uc j,ui t)
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
		delay(1000);
		}

	/*	we(5);
		P0=du[n[5]];
		delay(500);
		P0=0;
		we(4);
		P0=du[n[4]];
		delay(500);
		P0=0;
		we(1);
		P0=du[n[1]];
		delay(500);
		P0=0;
		we(0);
		P0=du[n[0]];
		delay(500);
		P0=0;
		*/
}
   bit keysta;
	 uc keynum;
int key()       //key()
{
	char a=0;
	P1=0x0f;
	if(P1!=0x0f)
	{
		delay(1000);
		if(P1!=0x0f)
		{	
			keysta=1;
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
     ui t=0;
		 unsigned char tmp;
uc   data1 = 0;
unsigned int  num1 = 0,num2 = 0,fu = 0;
float num3=0;
uc q[6] = {0};
bit  flag = 0;
int a = 0;
int c = 0; 
void send_char(uc txd);
void send(float  u);
void main()
{
    uart();
	while(1)
	{
		if(RI == 1)					
		{
			   RI = 0;		
				data1 = SBUF;	
			if(( data1>='0') && (data1<='9'))                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
			{
				num1 = 10*num1+(data1 -'0');
			}			
			else if(data1 == '+'||data1 =='-'||data1 == '*'|| data1 == '/')
				{
					fu = data1;
					num2 = num1;
					num1 = 0;
				}			
				else if(data1 == '='&&fu == '+')
				{
					num3 = num1+num2*1.0;
					flag = 1;
					
				}
				else if(data1 == '='&&fu == '-')
				{
					num3 = num2-num1*1.0;
					flag = 1;
				}
				else if(data1 == '='&&fu == '*')
				{
					num3 = num1*(num2*1.0);
					flag = 1;
				}
				else if(data1 == '='&&fu == '/')
				{
					num3 = num1/(num2*1.0);
				  flag = 1;
				}
			
			
			if(flag == 1)
			{
				send(num3);
				num1=0;
				num2=0;
				num3=0;
			  flag = 0;
			}
		}		
	}
}
void send_char(uc txd)

{
  P2=txd;
	delay(1e10);
	SBUF = txd;
	
	while(!TI);				
	TI = 0;				
	
}

void send(float u)
{
  ui v;
  uc i = 0;
	v=u*100+0.5;
	while(v>0)
	{
		c = v%10;
		if(i==2)  
		{
		     q[i]='.';
				 i++;
		}
		q[i] = c + '0';
		v = v/10;
		i++;
	}
	while(i+1)
	{
		send_char(q[i]);
		i--;
	}
	}