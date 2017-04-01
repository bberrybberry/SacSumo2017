/*
 * ir.h
 *
 *  Created on: Apr 1, 2017
 *      Author: bbhig
 */

#ifndef IR_H_
#define IR_H_

#define	IR_FL	0x01
#define	IR_FR	0x02
#define	IR_SL	0x00
#define	IR_SR	0x03


void IR_init(unsigned char irSensor);
unsigned char IR_getOutput(unsigned char irSensor);



#endif /* IR_H_ */
