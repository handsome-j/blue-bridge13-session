#ifndef __DS1302_H
#define __DS1302_H

extern unsigned char WRITE_RTC_ADDR[8];
extern unsigned char READ_RTC_ADDR[8];
extern unsigned char TIME[7];


/*ʱ���� û��ʲô����*/
void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte( unsigned char address );


/**/
void DS1302_Config();//����ʱ�Ӳ������� ��TIME�����е�ʱ�������
void DS1302_ReadTime();//����ʱ�����ݶ�ȡ����

#endif
