/*
 * ir.c
 *
 *  Created on: Apr 1, 2017
 *      Author: Aaron
 */

#include "ir.h"
#include "msp430f5529.h"

void IR_init(unsigned char irSensor) {
	P7DIR &= ~irSensor;
}

unsigned char IR_getOutput(unsigned char irSensor) {
	return (~P7IN & irSensor);
}
