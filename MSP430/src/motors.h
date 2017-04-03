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
#define MOTOR_IN_PORT_1 GPIO_PORT_P2 //B-AIN1 B-AIN2 B-BIN1
#define MOTOR_IN_PORT_2 GPIO_PORT_P3 //F-AIN1 B-BIN2
#define MOTOR_IN_PORT_3 GPIO_PORT_P7 //F-AIN2 F-BIN1 F-BIN2
#define MOTOR_IN_PIN_B-AIN1 GPIO_PIN5 //2.5
#define MOTOR_IN_PIN_B-AIN2 GPIO_PIN6 //2.6
#define MOTOR_IN_PIN_B-BIN1 GPIO_PIN7 //2.7
#define MOTOR_IN_PIN_F-AIN1 GPIO_PIN5 //3.5
#define MOTOR_IN_PIN_B-BIN2 GPIO_PIN6 //3.6
#define MOTOR_IN_PIN_F-AIN2 GPIO_PIN5 //7.5
#define MOTOR_IN_PIN_F-BIN1 GPIO_PIN6 //7.6
#define MOTOR_IN_PIN_B-BIN2 GPIO_PIN7 //7.7
#define F_PWMA_PORT GPIO_PORT_P1 //TODO: Other 3 PWM defines
#define F_PWMA_PIN GPIO_PIN1
#define F_ENABLE_PORT GPIO_PORT_P1
#define F_ENABLE_PIN GPIO_PIN5

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
