#ifndef _STDHEAD.H_
#define _STDHEAD.H_
#include <reg52.h>
#include <math.h>
#include <intrins.h>
typedef unsigned int ui;
typedef unsigned char uc;
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
void we(char i);
ui th1,tl1,th0,tl0;
void timer0(ui t);
void timer1(ui t);
void uart ();
void display(uc j,ui t);
uc keynum=-1;
int key();
#endif