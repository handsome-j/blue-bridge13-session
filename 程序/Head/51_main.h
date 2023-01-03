 #ifndef _51_MAIN_H
#define  _51_MAIN_H

#include "51_main.h"
#include <STC15F2K60S2.H>
#include "intrins.h"
#include "onewire.h"
#include "ds1302.h"
#include "math.h"

#define S7 P30
#define S6 P31
#define S5 P32
#define S4 P33


sbit L1=P4^4;//ап
sbit L2=P4^2;

extern unsigned char code led[];
extern unsigned char code led_point[];
extern unsigned int keyflag[20];

void delay(unsigned long int i);
void System_Init();
void display_bit(unsigned char pos,unsigned char a);
void Enable138(unsigned char num);


#endif