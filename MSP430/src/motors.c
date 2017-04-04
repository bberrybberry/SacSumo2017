/**
 *
 */

#include "motors.h"
#include "driverlib.h"

/**
 * Globals
 */
uint16_t timer_period_g;
uint16_t motor_speed_g;

void motorsInit(){

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5);


    //init digital direction inputs
    GPIO_setAsOutputPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN1 | MOTOR_IN_PIN_B_AIN2 | MOTOR_IN_PIN_B_BIN1);
    GPIO_setAsOutputPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_F_AIN1 | MOTOR_IN_PIN_B_BIN2);
    GPIO_setAsOutputPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_AIN2 | MOTOR_IN_PIN_F_BIN1 | MOTOR_IN_PIN_F_BIN2);


    //init PWM: 50%;
    timer_period_g = 1000;
    motor_speed_g = 950;
    //P1.1-4 as PWM output
    GPIO_setAsPeripheralModuleFunctionOutputPin(PWM_PORT, F_PWMA_PIN | F_PWMB_PIN | B_PWMA_PIN | B_PWMB_PIN);
    //Generate PWM on A0.0 - Timer runs in Up mode
    Timer_A_outputPWMParam FPWMA = {0};
    FPWMA.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    FPWMA.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    FPWMA.timerPeriod = timer_period_g;
    FPWMA.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    FPWMA.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    FPWMA.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &FPWMA);

    //Generate PWM on A0.1 - Timer runs in Up mode
    Timer_A_outputPWMParam FPWMB = {0};
    FPWMB.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    FPWMB.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    FPWMB.timerPeriod = timer_period_g;
    FPWMB.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    FPWMB.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    FPWMB.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &FPWMB);

    //Generate PWM on A0.2 - Timer runs in Up mode
    Timer_A_outputPWMParam BPWMA = {0};
    BPWMA.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    BPWMA.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    BPWMA.timerPeriod = timer_period_g;
    BPWMA.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    BPWMA.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    BPWMA.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &BPWMA);

    //Generate PWM on A0.3 - Timer runs in Up mode
    Timer_A_outputPWMParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    param.timerPeriod = timer_period_g;
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    param.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &param);

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

void setFrontMotorA(direction dir){
    if(dir == CW){
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_F_AIN1);
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_AIN2);
    }
    else if(dir == CCW){
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_F_AIN1);
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_AIN2);
    }
    else if(dir == SHORT_BRAKE){
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_F_AIN1);
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_AIN2);
    }
    else if(dir == STOP){
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_F_AIN1);
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_AIN2);
    }
}
void setFrontMotorB(direction dir){
    if(dir == CW){
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_BIN1);
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_BIN2);
    }
    else if(dir == CCW){
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_BIN1);
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_BIN2);
    }
    else if(dir == SHORT_BRAKE){
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_BIN1);
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_BIN2);
    }
    else if(dir == STOP){
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_BIN1);
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_BIN2);
    }
}
void setBackMotorA(direction dir){
    if(dir == CW){
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN1);
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN2);
    }
    else if(dir == CCW){
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN1);
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN2);
    }
    else if(dir == SHORT_BRAKE){
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN1);
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN2);
    }
    else if(dir == STOP){
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN1);
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN2);
    }
}
void setBackMotorB(direction dir){
    if(dir == CW){
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_BIN1);
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_B_BIN2);
    }
    else if(dir == CCW){
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_BIN1);
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_B_BIN2);
    }
    else if(dir == SHORT_BRAKE){
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_BIN1);
        GPIO_setOutputHighOnPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_B_BIN2);
    }
    else if(dir == STOP){
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_BIN1);
        GPIO_setOutputLowOnPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_B_BIN2);
    }
}