#include <REGX52.H>
#include <intrins.h>
#include <ir.h>
#include <h.h>
#include <lcd1602.h>
sbit moter=P1^0;

unsigned char number=50;
unsigned char adress=0;
unsigned char command=0;

void Delay100us()		//@11.0592MHz
{
	unsigned char i = 0;

	_nop_();
	i = 43;
	while (--i);
}


void main()
{
	Timer1Init();
	ir_init();
	LCD_Init();
	while(1)
	{
		
		LCD_ShowNum(  1, 1, number,3);
		Delay100us();
		
		if(ir_getdata()||ir_getrepeat())
		{
			adress=ir_getadress();
			command=ir_getcommand();
			if(command==0x02)
			{
				number-=10;
				if(number<=0) number = 0;
			}
			if(command==0x03)
			{
				number+=10;
				if(number>=100) number=100;
			
			}
			if(command==0x12)
			{
				number=0;
			}
		}
	}
}

void runtime(void) interrupt 3
{
	static unsigned char count=0;
	TL1 = 0xA4;		
	TH1 = 0xFF;	
	count+=1;
	
	if(count>=100)	count=0;
	
	if(count<number)
	{
		moter=1;
	}
	else
	{
		moter=0;
	}
}
