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
	 				 static bit t=0;
	 static  int i=0,m=0,s=129;
     static	int j=0,k=0;


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

	    timer0();
     while(i!=3);
	    EA=0;
	    P2=0xff;
	   while(1);
	
}

void exit() interrupt 1
{


     	TH0=0XFC;
	     TL0=0X18;	
	      k++;
	    			
	     if (j<=5-2*i&&t==0)
	     {
				 j++;
				 m=pow(2,i);
				 m=m<<j;
				 m=m|s;
				 m=~m;
				 P2=m;
				 delay(3000);
			 }
			 else 
			 {
				 t=1;
				 j--;
				 m=pow(2,i);
				 m=m<<j;
				 m=m|s;
				 m=~m;
				 P2=m;
				 delay(3000);
				 if(j<2*i) t=0;
      	 }
	
			   if(k==20)
				 {
					 k=0;
					 i++;
					 s=pow(2,i)+pow(2,7-i);
				 }
				 		
}