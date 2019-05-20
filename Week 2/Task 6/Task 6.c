#include<reg52.h>
#include<math.h>
#define  A  ((z=key())==-1)||((z=key())==10)
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
static char keynum;
char code du[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	                                     0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0};
char buf[8];
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

void divide(int i)      //led buf
{
	int t=1;
	char r;
	for(r=0;r<8;r++)
	{ 
		  buf[r]=i/t%10;
		  t=t*10;
	}
	for(r=7;r>=0;r--)
	{ 
		if(buf[r]==0) buf[r]=16;
		else break;
	}
}

static int t,s;
void display(int t)
{
	char n[4],i,m=1;
	for(i=0;i<4;i++)
	{
		n[i]=t%10;
		t=t/10;
	}
		for(i=3;i>0;i--)
	{ 
		if(n[i]==0)   n[i]=16;
		if(	n[i-1]!=0)   break;
	}
	for(i=3;i>=0;i--)
	{
	   P0=0;
		we(i);
		m=n[i];
		P0=du[m];
		delay(100);
	}
}

void see(int i,char j)
{
	   we(j);
	   
	    i=i/pow(10,j);
	    if(i%10!=0)
	   P0=du[i%10];
	   
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
int z;      //z=0
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
				case(0X70):	keynum=keynum;break;
				case(0Xb0): keynum=keynum+4;break;
				case(0Xd0): keynum=keynum+8;break;
				case(0Xe0):	keynum=keynum+12;break;
			}
			while((a<50)&&(P1!=0xf0))	 
			{
				delay(1000);
				a++;
			}	
			if (keynum==10)    return 2;
			else return 0;
		}
		else return 1;
	}
    else return 1;
}


char u=0;
bit g=0;
char q,j;
void main()
{	
    

		D:;
		delay(1e6);		
	 while(key()) display(t);
     if(keynum<10) t=keynum,s=t;
				G:;
		    delay(1e6);
				
	 while(z=key())   { if(z==2) {t=0;goto D; } display(t);}
		delay(1e6);
    if(keynum<10) t=t*10+keynum,s=t;
		else goto E;

    while(z=key())    {  if(z==2) {t=t/10;goto G;}display(t);    }

			E:;
		if(keynum==12) q=1;
		if(keynum==13) q=2;
	  if(keynum==14) q=3;
			if(keynum==15) q=4;
			t=0;
			H:;
   delay(1e6);		

	 while(z=key())   display(t);
		if(keynum<10) t=keynum;
		J:;
      delay(1e6);		
     while(z=key())    {   if(z==2) {t=0;goto H;}display(t);  }
		if(keynum<10) t=t*10+keynum;
		else goto F;
		
        delay(1e6);		
			while(z=key()) 
			{  
			if(z==2)   
			{t=t/10; goto J;}
			display(t); 
			}
				F:;
			if(q==1) t=t+s;
	   	if(q==2) t=s-t;
    	if(q==3) t=t*s;
			if( q==4)t=s/t;
			while(1)  display(t);
	
}


   


