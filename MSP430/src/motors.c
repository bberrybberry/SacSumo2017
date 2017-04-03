/**
 *
 */

#include "motors.h"
#include "driverlib.h"

/**
 * Globals
 */
uint8_t timer_period_g;
uint8_t motor_speed_g;

void init(){
    //init digital direction inputs
    GPIO_setAsOutputPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B-AIN1 | MOTOR_IN_PIN_B-AIN2 | MOTOR_IN_PIN_B-BIN1);
    GPIO_setAsOutputPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_F-AIN1 | MOTOR_IN_PIN_B-BIN2);
    GPIO_setAsOutputPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F-AIN2 | MOTOR_IN_PIN_F-BIN1 | MOTOR_IN_PIN_B-BIN2);


    //init PWM: 50%;
    timer_period_g = 1000;
    motor_speed_g = 950;
    //P1.3 as PWM output
    GPIO_setAsPeripheralModuleFunctionOutputPin(PWM_PORT, F_PWMA_PIN | F_PWMB_PIN | B_PWMA_PIN | B_PWMB_PIN);
    //Generate PWM on A0.0 - Timer runs in Up mode
    Timer_A_outputPWMParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    param.timerPeriod = timer_period_g;
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    param.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &param);

    //TODO: Init other three PWM

}


void setSpeed(unsigned char pin, unsigned char duty) {

}

void setDir(motorDir dir) {

	switch(dir) {
	case FORWARD:
		// set FAIN1 = OFF	FAIN2 = ON
		// set FBIN2 = OFF	FBIN2 = ON
		// set BAIN1 = OFF	BAIN2 = ON
		// set BBIN1 = OFF	BBIN2 = ON
		break;
	case BACKWARD:
		// set FAIN1 = ON	FAIN2 = OFF
		// set FBIN2 = ON	FBIN2 = OFF
		// set BAIN1 = ON	BAIN2 = OFF
		// set BBIN1 = ON	BBIN2 = OFF
		break;
	case LEFT:
		// set FAIN1 = ON	FAIN2 = OFF
		// set FBIN1 = OFF	FBIN2 = ON
		// set BAIN1 = ON	BAIN2 = OFF
		// set BBIN2 = OFF	BBIN2 = ON
		break;
	case RIGHT:
		// set FAIN1 = OFF	FAIN2 = ON
		// set FBIN1 = ON	FBIN2 = OFF
		// set BAIN1 = OFF	BAIN2 = ON
		// set BBIN1 = ON	BBIN2 = OFF
		break;
	case SOFT_BRAKE:
		// set FAIN1 = ON	FAIN2 = ON
		// set FBIN1 = ON	FBIN2 = ON
		// set BAIN1 = ON	BAIN2 = ON
		// set BBIN1 = ON	BBIN2 = ON
		break;
	case HARD_BRAKE:
		// set FAIN1 = OFF	FAIN2 = OFF
		// set FBIN1 = OFF	FBIN2 = OFF
		// set BAIN1 = OFF	BAIN2 = OFF
		// set BBIN1 = OFF	BBIN2 = OFF
		break;
	default:
		break;
	}
}
