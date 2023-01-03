#ifndef __DS1302_H
#define __DS1302_H

extern unsigned char WRITE_RTC_ADDR[8];
extern unsigned char READ_RTC_ADDR[8];
extern unsigned char TIME[7];


/*时序函数 没有什么卵用*/
void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte( unsigned char address );


/**/
void DS1302_Config();//日历时钟参数配置 把TIME数组中的时分秒存入
void DS1302_ReadTime();//日历时钟数据读取函数

#endif
