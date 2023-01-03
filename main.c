#include "51_main.h"


void keyscan();
void keyout();
void Display();
void Tim_init();

void S12out();
void S13out();
void S16out();
void S17out();

void tem_pro();
void led_pro();
void relay_pro();

int ledflag[4]={0};
unsigned int scence=0,model=0;
unsigned int T0_cnt=0,T1_cnt=0;


unsigned int tem_big=0,tem_settle=23;
float tem_value;

/*
scence 0 温度显示界面 1时间显示 2 参数设置
model 0 温度设置 1时间设置
*/
int main()
{
	System_Init();
	Tim_init();
	DS1302_Config();
	while(1)
	{
		
		DS1302_ReadTime();
		keyscan();
		keyout();
		
		relay_pro();
		tem_pro();
		led_pro();

		Display();
	}
}

void relay_pro()
{
		if(tem_value>tem_settle) 
		{P0=0x10;Enable138(5);Enable138(0);TR1=1;}
	else  
		{P0=0x00;Enable138(5);Enable138(0);TR1=0;ledflag[3]=0;}
}

void Tim0_INT() interrupt 1
{
	T0_cnt++; //50ms
	if(T0_cnt>=100) //5s
	{
		T0_cnt=0;
		ledflag[1]=0;
		P0=0x00;
		Enable138(5);
		Enable138(0);
		ledflag[3]=0;
		TR0=0;TR1=0;
		
	}
	
}
void Tim1_INT()  interrupt 3
{
	T1_cnt++;
	if(T1_cnt>=100)
	{
		T1_cnt=0;
		ledflag[3]=1-ledflag[3];
	}
}
void led_pro()
{
	if(TIME[0]==0&&TIME[1]==0) 
	{
		TR0=1;
		ledflag[1]=1;
		P0=0x10;
		Enable138(5);
		Enable138(0);
		TR1=1;
	}
			
			
	if(model==1) 
		ledflag[2]=1;
	else 
		ledflag[2]=0;
	
	
	
	P0=0xff;
	if(ledflag[1]) P00=0;
	if(ledflag[2]) P01=0;
	if(ledflag[3]) P02=0;
	Enable138(4);
	Enable138(0);
	
	
	
	
}
void tem_pro()
{
	tem_value=Ds18b20_Get_data();
	tem_big=10*tem_value;

		
	
}
void S12out()
{
	scence++;
	if(scence==3)
	{
		scence=0;
	}
}

void S13out()
{
	model=1-model;
	//模式切换
} 

void S16out()
{
	if(scence==2)
	{
		tem_settle=tem_settle+1;
		if(tem_settle>=99) tem_settle=99;
	}
}

void S17out()
{
	if(scence==2)
	{
		tem_settle=tem_settle-1;
		if(tem_settle<=10) tem_settle=10;
		
	}
	
}


void Display()
{
	if(scence==0)
	{
		display_bit(1,0xC1);
		display_bit(2,led[1]);
		display_bit(6,led[tem_big/100]);
		display_bit(7,led_point[tem_big/10%10]);
		display_bit(8,led[tem_big%10]);
	}
	else if(scence==1)
	{
		display_bit(1,0xC1);
		display_bit(2,led[2]);
		display_bit(4,led[TIME[2]/10]);
		display_bit(5,led[TIME[2]%10]);
		display_bit(6,0xbf);
		display_bit(7,led[TIME[1]/10]);
		display_bit(8,led[TIME[1]%10]);
	}
	else if(scence==2)
	{
		display_bit(1,0xC1);
		display_bit(2,led[3]);
		display_bit(7,led[tem_settle/10]);
		display_bit(8,led[tem_settle%10]);		
	}
}	

void keyout()     	
{
	if(keyflag[12]==1) {keyflag[12]=0;S12out();}
	if(keyflag[13]==1) {keyflag[13]=0;S13out();}
	if(keyflag[16]==1) {keyflag[16]=0;S16out();}
	if(keyflag[17]==1) {keyflag[17]=0;S17out();}
	
}
void Tim_init()
{
	EA=1;
	TMOD=0x00;//16位重载
	TH0=0x3c;
	TL0=0xb0;//50ms
	ET0=1;
	TR0=0;
	
	TH1=0xfc;
	TL1=0x18;
	ET1=1;
	TR1=0;
	
}
void keyscan()
{
	 int temp=0;
	
	P44=1;P42=1;P3=0xdf;temp=P3;temp=temp&0x0f;
	if(temp!=0x0f)
	{
		delay(20);temp=P3;temp=temp&0x0f;
		if(temp!=0x0f)
		{
			temp=P3;
			switch(temp)
			{
				case 0xdb: keyflag[13]=1;break;  //13
				case 0xd7: keyflag[12]=1;break;  //12
			}
		}
		while(temp!=0x0f)
		{
			temp=P3;
			temp=temp&0x0f;
		}
	}
	
	P44=1;P42=1;P3=0xef;temp=P3;temp=temp&0x0f;
	
	if(temp!=0x0f)
	{
		delay(20);temp=P3;temp=temp&0x0f;
		if(temp!=0x0f)
		{
			temp=P3;
			switch(temp)
			{	
				case 0xeb: keyflag[17]=1;break;  //17
				case 0xe7: keyflag[16]=1;break;  //16
			}
		}
		while(temp!=0x0f)
		{
			temp=P3;
			temp=temp&0x0f;
			if(keyflag[17]==1&&scence==1)
			{
				DS1302_ReadTime();
				display_bit(1,0xC1);
				display_bit(2,led[2]);
				display_bit(4,led[TIME[1]/10]);
				display_bit(5,led[TIME[1]%10]);
				display_bit(6,0xbf);
				display_bit(7,led[TIME[0]/10]);
				display_bit(8,led[TIME[0]%10]);
			}
		}

	}
}

		








