/**
 *
 */

#include <stdint.h>
#include "driverlib.h"

#ifndef MOTORS_H_
#define MOTORS_H_

/**
 * Global variables
 */
//uint8_t ain1Port;
//uint8_t ain1Pin;
//uint8_t ain2Port;
//uint8_t ain2Pin;
//uint8_t PWMAPort;
//uint8_t PWMAPin;


/**
 * Defines
 */

//TODO: everything for motor B and back motors
#define MOTOR_IN_PORT /**/ //port 7
#define MOTOR_IN_A_PIN /**/ //p7.5
#define MOTOR_IN_B_PIN /**/ //p7.6
#define MOTOR_IN_C_PIN /**/ //p7.7
#define F_PWMA_PORT /**/
#define F_PWMA_PIN /**/
#define F_ENABLE_PORT /**/
#define F_ENABLE_PIN /**/

#define ON	1
#define OFF ~ON

/**
 * Enums
 */
typedef enum{
    FORWARD, BACKWARD, LEFT, RIGHT, SOFT_BRAKE, HARD_BRAKE
} motorDir;

/**
 * Initialize the motor driver
 */
void init(void);

void setSpeed(unsigned char pin, unsigned char duty);
void setDir(motorDir dir);


#endif /* MOTORS_H_ */
