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
<<<<<<< HEAD
    /*
     * Last minute corrections:
     *
     * Some PWM signals got screwy, so now each driver gets the same signal to
     * PWMA and PWMB shorted acrossed the test points at the top of the board.
     */
    GPIO_setAsPeripheralModuleFunctionOutputPin(PWM_PORT, F_PWMB_PIN | B_PWMB_PIN);
    GPIO_setAsInputPin(PWM_PORT, F_PWMA_PIN | B_PWMA_PIN);

    //Generate PWM on A0.1 - Timer runs in Up mode
    Timer_A_outputPWMParam FPWM = {0};
    FPWM.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    FPWM.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    FPWM.timerPeriod = timer_period_g;
    FPWM.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    FPWM.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    FPWM.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &FPWM);

    //Generate PWM on A0.3 - Timer runs in Up mode
    Timer_A_outputPWMParam BPWM = {0};
    BPWM.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    BPWM.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    BPWM.timerPeriod = timer_period_g;
    BPWM.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    BPWM.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    BPWM.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &BPWM);
=======
    GPIO_setAsPeripheralModuleFunctionOutputPin(PWM_PORT, F_PWMA_PIN | F_PWMB_PIN | B_PWMA_PIN | B_PWMB_PIN);
    //Generate PWM on A0.0 - Timer runs in Up mode
    FPWMA.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    FPWMA.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    FPWMA.timerPeriod = timer_period_g;
    FPWMA.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    FPWMA.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    FPWMA.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &FPWMA);

    //Generate PWM on A0.1 - Timer runs in Up mode
    FPWMB.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    FPWMB.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    FPWMB.timerPeriod = timer_period_g;
    FPWMB.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    FPWMB.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    FPWMB.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &FPWMB);

    //Generate PWM on A0.2 - Timer runs in Up mode
    BPWMA.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    BPWMA.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    BPWMA.timerPeriod = timer_period_g;
    BPWMA.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    BPWMA.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    BPWMA.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &BPWMA);

    //Generate PWM on A0.3 - Timer runs in Up mode
    BPWMB.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    BPWMB.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    BPWMB.timerPeriod = timer_period_g;
    BPWMB.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    BPWMB.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    BPWMB.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &BPWMB);
>>>>>>> 532a4adfe53c8dbf44c93f9ea3f8e53f73c7db8d

}


void setSpeed(uint8_t pin, uint16_t duty) {
	switch(pin) {
	case F_PWMA_PIN:
		motor_speed_g = duty;
		FPWMA.dutyCycle = motor_speed_g;
		Timer_A_outputPWM(TIMER_A0_BASE, &FPWMA);
		break;
	case F_PWMB_PIN:
		motor_speed_g = duty;
		FPWMB.dutyCycle = motor_speed_g;
		Timer_A_outputPWM(TIMER_A0_BASE, &FPWMB);
		break;
	case B_PWMA_PIN:
		motor_speed_g = duty;
		BPWMA.dutyCycle = motor_speed_g;
		Timer_A_outputPWM(TIMER_A0_BASE, &BPWMA);
		break;
	case B_PWMB_PIN:
		motor_speed_g = duty;
		BPWMB.dutyCycle = motor_speed_g;
		Timer_A_outputPWM(TIMER_A0_BASE, &BPWMB);
		break;
	default:
		break;
	}
}
<<<<<<< HEAD

void setDir(botDir dir) {

	switch(dir) {
	case FORWARD:
	    setFrontMotorA(CW);
	    setFrontMotorB(CW);
	    setBackMotorA(CW);
	    setBackMotorB(CW);
		break;
	case BACKWARD:
	    setFrontMotorA(CCW);
	    setFrontMotorB(CCW);
	    setBackMotorA(CCW);
	    setBackMotorB(CCW);
		break;
	case LEFT:
	    setFrontMotorA(CW);
	    setFrontMotorB(CW);
	     setBackMotorA(CCW);
	     setBackMotorB(CCW);
		break;
	case RIGHT:
	    setFrontMotorA(CCW);
	    setFrontMotorB(CCW);
	     setBackMotorA(CW);
	     setBackMotorB(CW);
		break;
	case SOFT_BRAKE:
	    setFrontMotorA(SHORT_BRAKE);
	    setFrontMotorB(SHORT_BRAKE);
	     setBackMotorA(SHORT_BRAKE);
	     setBackMotorB(SHORT_BRAKE);
		break;
	case HARD_BRAKE:
	    setFrontMotorA(STOP);
	    setFrontMotorB(STOP);
	     setBackMotorA(STOP);
	     setBackMotorB(STOP);
=======
// Motor A: Right
// Motor B: Left
void setDir(motorDir dir) {

	switch(dir) {
	case FORWARD:
		// set FAIN1 = OFF	FAIN2 = ON
		// set FBIN2 = OFF	FBIN2 = ON
		// set BAIN1 = OFF	BAIN2 = ON
		// set BBIN1 = OFF	BBIN2 = ON
		setFrontMotorA(CW);
		setFrontMotorB(CW);
		setBackMotorA(CW);
		setBackMotorB(CW);
		break;
	case BACKWARD:
		// set FAIN1 = ON	FAIN2 = OFF
		// set FBIN2 = ON	FBIN2 = OFF
		// set BAIN1 = ON	BAIN2 = OFF
		// set BBIN1 = ON	BBIN2 = OFF
		setFrontMotorA(CCW);
		setFrontMotorB(CCW);
		setBackMotorA(CCW);
		setBackMotorB(CCW);
		break;
	case LEFT:
		// set FAIN1 = ON	FAIN2 = OFF
		// set FBIN1 = OFF	FBIN2 = ON
		// set BAIN1 = ON	BAIN2 = OFF
		// set BBIN2 = OFF	BBIN2 = ON
		setFrontMotorA(CW);
		setFrontMotorB(CCW);
		setBackMotorA(CW);
		setBackMotorB(CCW);
		break;
	case RIGHT:
		// set FAIN1 = OFF	FAIN2 = ON
		// set FBIN1 = ON	FBIN2 = OFF
		// set BAIN1 = OFF	BAIN2 = ON
		// set BBIN1 = ON	BBIN2 = OFF
		setFrontMotorA(CCW);
		setFrontMotorB(CW);
		setBackMotorA(CCW);
		setBackMotorB(CW);
		break;
	case SOFT_BRAKE:
		// set FAIN1 = ON	FAIN2 = ON
		// set FBIN1 = ON	FBIN2 = ON
		// set BAIN1 = ON	BAIN2 = ON
		// set BBIN1 = ON	BBIN2 = ON
		setFrontMotorA(SOFT_BRAKE);
		setFrontMotorB(SOFT_BRAKE);
		setBackMotorA(SOFT_BRAKE);
		setBackMotorB(SOFT_BRAKE);
		break;
	case HARD_BRAKE:
		// set FAIN1 = OFF	FAIN2 = OFF
		// set FBIN1 = OFF	FBIN2 = OFF
		// set BAIN1 = OFF	BAIN2 = OFF
		// set BBIN1 = OFF	BBIN2 = OFF
		setFrontMotorA(STOP);
		setFrontMotorB(STOP);
		setBackMotorA(STOP);
		setBackMotorB(STOP);
>>>>>>> 532a4adfe53c8dbf44c93f9ea3f8e53f73c7db8d
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
