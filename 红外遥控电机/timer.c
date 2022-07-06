#include <REGX52.H>
void Timer0Init(void)		
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0x00;		
	TH0 = 0x00;		
	TF0 = 0;		
	TR0 = 0;		
}

void timer0_set_time(unsigned int time)
{
	TH0=time/256;
	TL0=time%256;
}

unsigned int timer0_read_time(void)
{
	return ((unsigned int)TH0)<<8 | (unsigned int)TL0 ;
}

void timer0_run(unsigned char flag)
{
	TR0 = flag;
}