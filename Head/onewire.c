/*
  ����˵��: ��������������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨(�ⲿ����12MHz) STC89C52RC��Ƭ��
  ��    ��: 2011-8-9
*/
#include <STC15F2K60S2.H>

#include <onewire.h>

#define  DQ  P14  //�����߽ӿ�

//��������ʱ����
void Delay_OneWire(unsigned int t)  //STC89C52RC
{
	t=t*10;
	while(t--);
}

//ͨ����������DS18B20дһ���ֽ�
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

//��DS18B20��ȡһ���ֽ�
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

//DS18B20�豸��ʼ��
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
	Write_DS18B20(0xcc);//����ROM
	Write_DS18B20(0x44);//�����¶�ת������
//	Delay_OneWire(250);
	
	init_ds18b20();
	Write_DS18B20(0xcc);//����ROM
	Write_DS18B20(0xbe);//���Ͷ��ݴ�������
//	Delay_OneWire(250);
	
	low=Read_DS18B20();
	high=Read_DS18B20();
	
	init_ds18b20();
	temp=(low|(high<<8));
	temperature=temp*0.0625;
	return temperature;
}





