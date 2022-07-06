#ifndef __IR_H__
#define __IR_H__

void ir_init(void);
unsigned char ir_getdata(void);
unsigned char ir_getadress(void);
unsigned char ir_getcommand(void);
unsigned char ir_getrepeat(void);


#endif