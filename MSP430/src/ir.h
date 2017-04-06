/*
 * ir.h
 *
 *  Created on: Apr 1, 2017
 *      Author: bbhig
 */
/**
 * @file
 * @brief Header file for the infrared sensors
 */


#ifndef IR_H_
#define IR_H_


#define	IR_FL	0x02	/**> Front left sensor at P7.1*/
#define	IR_FR	0x04	/**> Front right sensor at P7.2*/
#define	IR_SL	0x01	/**> Side left sensor at P7.0*/
#define	IR_SR	0x08	/**> Side right sensor at P7.3*/

/**
 * @fn IR_init(unsigned char irSensor)
 * @param irSensor The address of which sensor is being addressed, get from defines
 */
void IR_init(unsigned char irSensor);

/**
 * @fn IR_getOutput(unsigned char irSensor)
 * @param irSensor The address of which sensor is being addressed, get from defines
 *
 */
unsigned char IR_getOutput(unsigned char irSensor);



#endif /* IR_H_ */
