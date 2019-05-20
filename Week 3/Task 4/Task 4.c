#include<reg52.h>
#include<math.h>
#define stop while(1);        //stop   for   debug
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
sbit beep=P1^5;
	char code du[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	                                     0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0};

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

void timer0()    
{
	TMOD=0X01;
	TH0=0XFC;
	TL0=0X18;	     // 1ms
	ET0=1;
	EA=1;
	TR0=1;	
}

void display(char j,int t)
{
	char n[8],i,m=1;
	for(i=0;i<j;i++)
	{
		n[i]=t%10;
		t=t/10;
	}
	/*	for(i=j;i>0;i--)
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
		*/
		we(5);
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
}
uc keynum;
int key()       //key()
{
	char a=0;
  static bit keysta;
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
 ui t=0,q=-1,q1,q2,q3,u=1;  
ui z=0;
 //static
void    see(ui t)
{
    we(5);
		P0=du[t/60/10];
		delay(100);
		P0=0;
		we(4);
		P0=du[t/60%10];
		delay(100);
		P0=0;
		we(1);
		P0=du[t%60/10];
		delay(100);
		P0=0;
		we(0);
		P0=du[t%60%10];
		delay(100);
		P0=0;
} 
bit flag=1;
void main()
{

      A:;

		 while(key()==-1);
		 if(keynum!=12)
		 goto A;
	
     timer0();	 

		 while(1) 
		 {
		       
		      if(key()==13)   flag=~flag;
           see(t);
		
			 if(keynum==14)  
			 {
			     EA=0;
					 z=0;
					 t=0;
					 goto A;
			 }
		
			 	if(keynum==15)
			{
			   u=0;
			    we(0);
					P0=du[0];
				 
				 	while(key()==-1||key()>9); 
		    
					while(key()==-1||key()>9)  see(q1=keynum*600);delay(1000);
						
					while(key()==-1||key()>9)  see(q2=q1+keynum*60);delay(1000);
			
					while(key()==-1||key()>9)  see(q3=q2+keynum*10);delay(1000);
		 
					while(key()==-1||key()>9)  see(q=q3+keynum);
           u=1;
				 
		       keynum=-1;			 
			}
			
			}
		 
		
}

void exit() interrupt 1
{
     
     	TH0=0XFC;
	    TL0=0X18;	 
			z++;			
			if(z==1000)
			{
          z=0;
				    	
					
					   if(flag&&u) t++;
						 
					if(t==3600)  t=0;				
			}	
      if(q==t)  q=-2;
			if(q==-2)   beep=~beep,delay(50);
}