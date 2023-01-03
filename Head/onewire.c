/*
  程序说明: 单总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台(外部晶振12MHz) STC89C52RC单片机
  日    期: 2011-8-9
*/
#include <STC15F2K60S2.H>

#include <onewire.h>

#define  DQ  P14  //单总线接口

//单总线延时函数
void Delay_OneWire(unsigned int t)  //STC89C52RC
{
	t=t*10;
	while(t--);
}

//通过单总线向DS18B20写一个字节
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
}

//从DS18B20读取一个字节
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);
	}
	return dat;
}

//DS18B20设备初始化
bit init_ds18b20(void)
{
  	bit initflag = 0;
  	
  	DQ = 1;
  	Delay_OneWire(12);
  	DQ = 0;
  	Delay_OneWire(80);
  	DQ = 1;
  	Delay_OneWire(10); 
    initflag = DQ;     
  	Delay_OneWire(5);
  
  	return initflag;
}

float Ds18b20_Get_data()
{
	unsigned char low, high;
	unsigned int temp;
	float temperature;
	init_ds18b20();
	Write_DS18B20(0xcc);//跳过ROM
	Write_DS18B20(0x44);//发送温度转换命令
//	Delay_OneWire(250);
	
	init_ds18b20();
	Write_DS18B20(0xcc);//跳过ROM
	Write_DS18B20(0xbe);//发送读暂存器命令
//	Delay_OneWire(250);
	
	low=Read_DS18B20();
	high=Read_DS18B20();
	
	init_ds18b20();
	temp=(low|(high<<8));
	temperature=temp*0.0625;
	return temperature;
}





