#include <stdio.h>
#include <stdlib.h>
#include<reg52.h>
#define uc unsigned char
#define ui unsigned int
sbit led0=P2^0;
sbit led2=P2^2;
sbit led4=P2^4;
sbit led6=P2^6;
void main()
{
	led0=0;
	led2=0;
	led4=0;
	led6=0;

}
