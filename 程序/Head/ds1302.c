#include <REG52.H>
#include <intrins.h>
#include "ds1302.h"
unsigned char  WRITE_RTC_ADDR[8] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
unsigned char  READ_RTC_ADDR[8] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};
unsigned char  TIME[7] = {0x01,0x00,0x00,0x00,0x00,0x00,0x00};//秒 分 时 日 月 星期 年
/*

*/
sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   // DS1302复位												

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	
	return (temp/16*10+temp%16);
}


void DS1302_Config()
{
	unsigned char n;
	Write_Ds1302_Byte(0x8E,0x00); 
	for(n=0; n<3; n++)						//修改7->3 对时分秒进行操作
	{
		Write_Ds1302_Byte(WRITE_RTC_ADDR[n],TIME[n]);
	}
	Write_Ds1302_Byte(0x8E,0x80); 
}
void DS1302_ReadTime()
{
	unsigned char n;
	for(n=0; n<3; n++)			//修改7->3 对时分秒进行操作
	{
		TIME[n] = Read_Ds1302_Byte(READ_RTC_ADDR[n]);
	}
}
