#include "51_main.h"
#include <STC15F2K60S2.H>
#include "intrins.h"

#include "onewire.h"
#include "ds1302.h"
#include "math.h"

unsigned char code led[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
unsigned char code led_point[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x08,0x03,0x36,0x21,0x06,0x0e};
unsigned int keyflag[20]={0};

void display_bit(unsigned char pos,unsigned char a)//Y7 输入断码 Y6 位置选择
{
	pos--;	
	P0 = (0x01<<pos);
	Enable138(6);
	Enable138(0);	
	P0 = a;
	Enable138(7);
	delay(1);
	P0 = 0xff;
	Enable138(0);
}

void delay(unsigned long int xms)//11.0592MHZ--delay--ms
{	
	unsigned long int i=90*xms;
	while(i--);
}

void System_Init()
{
	P0=0xff;
	Enable138(4);//关闭LED灯
	Enable138(7);//数码管
	Enable138(0);
	P0=0x00;
	Enable138(5);//蜂鸣器和继电器
	Enable138(0);

}
/*
num
4 LED
5 继电器
6 数码管位选
7 数码管断码
*/
void Enable138(unsigned char num)
{
	P2&=0x1f;
	P2|=num<<5;
}
