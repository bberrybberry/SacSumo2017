/**
 *
 */

#include <stdint.h>

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
#define F_AIN1_PORT /**/;
#define F_AIN1_PIN /**/;
#define F_AIN2_PORT /**/;
#define F_AIN2_PIN /**/;
#define F_PWMA_PORT /**/;
#define F_PWMA_PIN /**/;
#define F_ENABLE_PORT /**/;
#define F_ENABLE_PIN /**/;

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



#endif /* MOTORS_H_ */
