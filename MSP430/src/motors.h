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
#define MOTOR_IN_PIN_B_AIN1 GPIO_PIN5 //2.5
#define MOTOR_IN_PIN_B_AIN2 GPIO_PIN6 //2.6
#define MOTOR_IN_PIN_B_BIN1 GPIO_PIN7 //2.7
#define MOTOR_IN_PIN_F_AIN1 GPIO_PIN5 //3.5
#define MOTOR_IN_PIN_B_BIN2 GPIO_PIN6 //3.6
#define MOTOR_IN_PIN_F_AIN2 GPIO_PIN5 //7.5
#define MOTOR_IN_PIN_F_BIN1 GPIO_PIN6 //7.6
#define MOTOR_IN_PIN_F_BIN2 GPIO_PIN7 //7.7
#define PWM_PORT GPIO_PORT_P1
#define F_PWMA_PIN GPIO_PIN1
#define F_PWMB_PIN GPIO_PIN2
#define B_PWMA_PIN GPIO_PIN3
#define B_PWMB_PIN GPIO_PIN4
#define F_ENABLE_PORT GPIO_PORT_P1
#define F_ENABLE_PIN GPIO_PIN5

#define ON	1

#if ON
#define OFF 0
#else
#define OFF 1
#endif

/**
 * Enums
 */
typedef enum{
    FORWARD, BACKWARD, LEFT, RIGHT, SOFT_BRAKE, HARD_BRAKE
} motorDir;

typedef enum{ CW, CCW, SHORT_BRAKE, STOP } direction;

/**
 * Initialize the motor driver
 */
void init(void);

void setSpeed(unsigned char pin, unsigned char duty);
void setDir(motorDir dir);

void setFrontMotorA(direction dir);
void setFrontMotorB(direction dir);
void setBackMotorA(direction dir);
void setBackMotorB(direction dir);


#endif /* MOTORS_H_ */
