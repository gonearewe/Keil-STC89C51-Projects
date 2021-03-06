#include <reg52.h>

sbit ADDR0 = P2^4;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit KEY_IN_1  = P1^4;
sbit KEY_IN_2  = P1^5;
sbit KEY_IN_3  = P1^6;
sbit KEY_IN_4  = P1^7;
sbit KEY_OUT_1 = P1^3;
sbit KEY_OUT_2 = P1^2;
sbit KEY_OUT_3 = P1^1;
sbit KEY_OUT_4 = P1^0;

unsigned char code LedChar[] = {  //??????????
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71
};
unsigned char LedBuff[6] = {  //????????
    0, 0, 0, 0, 0, 0
};
unsigned char code KeyCodeMap[4][4] = { //?????????????????
    { 0x31, 0x32, 0x33, 0x26 }, //???1????2????3????
    { 0x34, 0x35, 0x36, 0x25 }, //???4????5????6????
    { 0x37, 0x38, 0x39, 0x28 }, //???7????8????9????
    { 0x30, 0x1B, 0x0D, 0x27 }  //???0?ESC??  ???? ???
};
unsigned char KeySta[4][4] = {  //???????????
    {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1}
};

void KeyDriver();

void main()
{
    EA = 1;       //?????
    //ENLED = 0;    //?????????
    //ADDR3 = 1;
    TMOD = 0x01;  //??T0???1
    TH0  = 0xFC;  //?T0???0xFC67,??1ms
    TL0  = 0x67;
    ET0  = 1;     //??T0??
    TR0  = 1;     //??T0
    LedBuff[0] = LedChar[0];  //????0
	
    while (1)
    {
        KeyDriver();   //????????
    }
}
/* ???????????????????,num-????? */
void ShowNumber(long num)
{
    signed char i;
    unsigned char sign;
    unsigned char buf[6];
    
    if (num < 0)  //??????????
    {
        sign = 1;
        num = -num;
    }
    else
    {
        sign = 0;
    }
    for (i=0; i<6; i++)   //????????6???????
    {
        buf[i] = num % 10;
        num = num / 10;
    }
    for (i=5; i>=1; i--)  //?????,??0?????,???0?????
    {
        if (buf[i] == 0)
            LedBuff[i] = 0;
        else
            break;
    }
    if (sign != 0)        //???,?????????
    {
        if (i < 5)        //???????6??????,??????????
        {
            LedBuff[i+1] = 0xBF;
        }
    }
    for ( ; i>=0; i--)    //?????????????????
    {
        LedBuff[i] = LedChar[buf[i]];
    }
}
/* ??????,???????????,keycode-???? */
void KeyAction(unsigned char keycode)
{
    static char oprt = 0;    //?????????
    static long result = 0;  //????????
    static long addend = 0;  //?????????
    
    if ((keycode>=0x30) && (keycode<=0x39))  //??0-9???
    {
        addend = (addend*10)+(keycode-0x30); //???????,???????
        ShowNumber(addend);    //??????????
    }
    else if (keycode == 0x26)  //???????
    {
        oprt = 0;              //???????
        result = addend;       //????????,??????
        addend = 0;            //?????,??????????
        ShowNumber(addend);    //???????
    }
    else if (keycode == 0x28)  //???????
    {
        oprt = 1;              //???????
        result = addend;       //????????,??????
        addend = 0;            //?????,??????????
        ShowNumber(addend);    //???????
    }
    else if (keycode == 0x0D)  //???,??????
    {
        if (oprt == 0)
        {
            result += addend;  //??????
        }
        else
        {
            result -= addend;  //??????
        }
        addend = 0;
        ShowNumber(result);    //??????????
    }
    else if (keycode == 0x1B)  //Esc?,????
    {
        addend = 0;
        result = 0;
        ShowNumber(addend);    //????????????
    }
}
/* ??????,??????,????????,???????? */
void KeyDriver()
{
    unsigned char i, j;
    static unsigned char backup[4][4] = {  //?????,???????
        {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1}
    };
    
    for (i=0; i<4; i++)  //????4*4?????
    {
        for (j=0; j<4; j++)
        {
            if (backup[i][j] != KeySta[i][j])    //??????
            {
                if (backup[i][j] != 0)           //?????????
                {
                    KeyAction(KeyCodeMap[i][j]); //????????
                }
                backup[i][j] = KeySta[i][j];     //?????????
            }
        }
    }
}
/* ??????,?????????,??????1ms */
void KeyScan()
{
    unsigned char i;
    static unsigned char keyout = 0;   //??????????
    static unsigned char keybuf[4][4] = {  //?????????
        {0xFF, 0xFF, 0xFF, 0xFF},  {0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF},  {0xFF, 0xFF, 0xFF, 0xFF}
    };

    //????4?????????
    keybuf[keyout][0] = (keybuf[keyout][0] << 1) | KEY_IN_1;
    keybuf[keyout][1] = (keybuf[keyout][1] << 1) | KEY_IN_2;
    keybuf[keyout][2] = (keybuf[keyout][2] << 1) | KEY_IN_3;
    keybuf[keyout][3] = (keybuf[keyout][3] << 1) | KEY_IN_4;
    //?????????
    for (i=0; i<4; i++)  //??4???,????4?
    {
        if ((keybuf[keyout][i] & 0x0F) == 0x00)
        {   //??4?????0,?4*4ms????????,???????????
            KeySta[keyout][i] = 0;
        }
        else if ((keybuf[keyout][i] & 0x0F) == 0x0F)
        {   //??4?????1,?4*4ms????????,???????????
            KeySta[keyout][i] = 1;
        }
    }
    //??????????
    keyout++;                //??????
    keyout = keyout & 0x03;  //?????4???
    switch (keyout)          //????,????????,?????????
    {
        case 0: KEY_OUT_4 = 1; KEY_OUT_1 = 0; break;
        case 1: KEY_OUT_1 = 1; KEY_OUT_2 = 0; break;
        case 2: KEY_OUT_2 = 1; KEY_OUT_3 = 0; break;
        case 3: KEY_OUT_3 = 1; KEY_OUT_4 = 0; break;
        default: break;
    }
}
/* ???????????,????????? */
void LedScan()
{
    static unsigned char i = 0;  //???????
    
    P0 = 0xFF;   //????
    switch (i)
    {
        case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=LedBuff[0]; break;
        case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=LedBuff[1]; break;
        case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=LedBuff[2]; break;
        case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=LedBuff[3]; break;
        case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=LedBuff[4]; break;
        case 5: ADDR2=1; ADDR1=0; ADDR0=1; i=0; P0=LedBuff[5]; break;
        default: break;
    }
}
/* T0??????,?????????????? */
void InterruptTimer0() interrupt 1
{
    TH0 = 0xFC;  //??????
    TL0 = 0x67;
    LedScan();   //???????????
    KeyScan();   //????????
}
