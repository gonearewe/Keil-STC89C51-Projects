#include <reg52.h>
#include <math.h>
#include <intrins.h>

typedef unsigned int ui;
typedef unsigned char uc;
sbit A=P1^0;
sbit k0=P3^0;
sbit k1=P3^1;
sbit k2=P3^2;
sbit k3=P3^3;
sbit led0=P2^0;
sbit led1=P2^1;
sbit SDA=P2^0;
sbit SCL=P2^1;
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
uc  code du[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	                                     0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0};
 void Delay10us()
{
	unsigned char a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);

}
 void delay(unsigned int i)   //i=1 10us
{
	while(i--);
}

void I2cStart()
{
 	SDA=1;
	delay(1);
	SCL=1;
	delay(1);
	SDA=0;
	delay(1);
	SCL=0;			
	delay(1);		
}

void I2cStop()
{
	SDA=0;
	delay(1);
	SCL=1;
	delay(1);
	SDA=1;
	delay(1);		
}

unsigned char I2cSendByte(unsigned char dat)
{
	unsigned char a=0,b=0;//最大255，一个机器周期为1us，最大延时255us。		
	for(a=0;a<8;a++)//要发送8位，从最高位开始
	{
		SDA=dat>>7;	
		dat=dat<<1;
		delay(1);
		SCL=1;
		delay(1);//建立时间>4.7us
		SCL=0;
		delay(1);//时间大于4us		
	}
	SDA=1;
	delay(1);
	SCL=1;
	while(SDA)//等待应答，也就是等待从设备把SDA拉低
	{
		b++;
		if(b>200)	 //如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
		{
			SCL=0;
			delay(1);
			return 0;
		}
	}
	SCL=0;
	delay(1);
 	return 1;		
}

unsigned char I2cReadByte()
{
	unsigned char a=0,dat=0;
	SDA=1;			//起始和发送一个字节之后SCL都是0
	delay(1);
	for(a=0;a<8;a++)//接收8个字节
	{
		SCL=1;
		delay(1);
		dat<<=1;
		dat|=SDA;
		delay(1);
		SCL=0;
		delay(1);
	}
	return dat;		
}

void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(0xa0);//发送写器件地址
	I2cSendByte(addr);//发送要写入内存地址
	I2cSendByte(dat);	//发送数据
	I2cStop();

}

unsigned char At24c02Read(unsigned char addr)
{
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa0); //发送写器件地址
	I2cSendByte(addr); //发送要读取的地址
	I2cStart();
	I2cSendByte(0xa1); //发送读器件地址
	num=I2cReadByte(); //读取数据
	I2cStop();
	return num;	
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
		//delay(1000);
		}
}
   bit keysta;
	 uc keynum=-1;
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
	uc t=0,k=0,c[20],i=0;	
	bit flag=0;
void main()
{
     
      uart();
			//if(At24c02Read(1)==0)    flag=1;
      while(1)
			{
			   if(RI==1)
				 {
				    t=SBUF;
						At24c02Write(22,t);
					}
					if(k0==0)
					{
					   	t=	At24c02Read(22);
					    SBUF=t;
					}
					}
			  /* key();
				 if(keynum==0)  t++;
				 if(keynum==1) At24c02Write(22,t);
				 	 if(keynum==2)  	t=	At24c02Read(22);
					 keynum=-1;
					 P2=t;
			}
			*/
		  while(1)
			{
		//	led7=flag;
			if(RI==1)
			{
			
		  for(i=0;i<20;i++)
			{
			    while(!RI);
					RI=0;
					c[i]=SBUF;
					At24c02Write(i+2,c[i]);
			}
			//At24c02Write(1,0);
			while(1)   {beep=~beep;delay(100);}
			}
			if(k1==0) {delay(1000);if(k1==0) led7=0, flag=1;}
      if(TI==1|flag)
			{

			 for(i=0;i<20;i++)
			{
			    while(!TI|flag);
					flag=0;
					TI=0;
					c[i]=	At24c02Read(i+2);
					SBUF=c[i];
				}
				
			}
			
			
	 }
}

