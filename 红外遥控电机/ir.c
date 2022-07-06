#include <REGX52.H>
#include <h.h>
#include <timer.h>

extern unsigned int ir_time=0;
extern unsigned char ir_state=0;
extern unsigned char ir_adress=0;
extern unsigned char ir_command=0;
extern unsigned char ir_data[4]={0};
extern unsigned int ir_pdata=0;
extern unsigned char ir_repeatflag=0;
extern unsigned char ir_dataflag=0;

void ir_init(void)
{
	Timer0Init();
	int0_init();
}

unsigned char ir_getdata(void)
{
	if(ir_dataflag)
	{
		ir_dataflag=0;
		return 1;
	}
	return 0;
}

unsigned char ir_getadress(void)
{
	return ir_adress;
}

unsigned char ir_getcommand(void)
{
	return ir_command;
}

unsigned char ir_getrepeat(void)
{
	if(ir_repeatflag)
	{
		ir_repeatflag=0;
		return 1;
	}
	return 0;
}

void runtimer(void)	interrupt 0
{
	if(ir_state==0)
	{
		timer0_set_time(0);
		timer0_run(1);
		ir_state=1;
	}
	else  if(ir_state==1)
	{	
		
		ir_time=timer0_read_time();
		timer0_set_time(0);
		if( ir_time > 12442-400  &&  ir_time < 12442+400 )//接收标志的上下400//晶振频率问题
		{
			ir_state=2;	
		}
		else if( ir_time > 10368-400  &&  ir_time < 10368+400 )//repeat标志的上下400
		{
			ir_repeatflag=1;
			timer0_run(0);
			ir_state=0;
		}
		else//error
		{
			ir_state=1;
		}
	}
	else if(ir_state==2)
	{
		ir_time=timer0_read_time();
		timer0_set_time(0);
		if( ir_time > 1032-400  &&  ir_time < 1032+400 )//0的上下400//晶振频率问题
		{
			ir_data[ir_pdata/8]&=~(0x01<<ir_pdata%8);
			ir_pdata++;
		}
		else if( ir_time > 2074-400  &&  ir_time < 2074+400 )//0的上下400//晶振频率问题
		{
			ir_data[ir_pdata/8]|=(0x01<<ir_pdata%8);
			ir_pdata++;
		}
		else
		{
			ir_state=1;
			ir_pdata=0;
		}
		if(ir_pdata>=32)
		{
			ir_pdata=0;
			if(	ir_data[0]==~ir_data[1]	&&	ir_data[2]==~ir_data[3])
			{
				ir_adress=ir_data[0];
				ir_command=ir_data[2];
				ir_dataflag=1;
			}
			timer0_run(0);
			ir_state=0;
		}
	}
}