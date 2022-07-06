#ifndef __TIMER_H__
#define __TIMER_H__

unsigned int timer0_read_time(void);

void timer0_set_time(unsigned int time);

void Timer0Init(void);

void timer0_run(unsigned char flag);

#endif