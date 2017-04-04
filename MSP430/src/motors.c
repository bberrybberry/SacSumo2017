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
Timer_A_outputPWMParam FPWM_g = {0};
Timer_A_outputPWMParam BPWM_g = {0};


void motorsInit(){

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5);

    //init digital direction inputs
    GPIO_setAsOutputPin(MOTOR_IN_PORT_1, MOTOR_IN_PIN_B_AIN1 | MOTOR_IN_PIN_B_AIN2 | MOTOR_IN_PIN_B_BIN1);
    GPIO_setAsOutputPin(MOTOR_IN_PORT_2, MOTOR_IN_PIN_F_AIN1 | MOTOR_IN_PIN_B_BIN2);
    GPIO_setAsOutputPin(MOTOR_IN_PORT_3, MOTOR_IN_PIN_F_AIN2 | MOTOR_IN_PIN_F_BIN1 | MOTOR_IN_PIN_F_BIN2);

    //init PWM: 90%;
    timer_period_g = 1000;
    motor_speed_g = 900;
    //P1.1-4 as PWM output
    /*
     * Last minute corrections:
     *
     * Some PWM signals got screwy, so now each driver gets the same signal to
     * PWMA and PWMB shorted acrossed the test points at the top of the board.
     */
    GPIO_setAsPeripheralModuleFunctionOutputPin(PWM_PORT, F_PWMB_PIN | B_PWMB_PIN);
    GPIO_setAsInputPin(PWM_PORT, F_PWMA_PIN | B_PWMA_PIN);

    //Generate PWM on A0.1 - Timer runs in Up mode
    Timer_A_outputPWMParam FPWM_g = {0};
    FPWM_g.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    FPWM_g.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    FPWM_g.timerPeriod = timer_period_g;
    FPWM_g.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    FPWM_g.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    FPWM_g.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &FPWM_g);

    //Generate PWM on A0.3 - Timer runs in Up mode
    Timer_A_outputPWMParam BPWM_g = {0};
    BPWM_g.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
    BPWM_g.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    BPWM_g.timerPeriod = timer_period_g;
    BPWM_g.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    BPWM_g.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    BPWM_g.dutyCycle = motor_speed_g;
    Timer_A_outputPWM(TIMER_A0_BASE, &BPWM_g);

}


void setSpeed(uint8_t pin, uint16_t duty) {
	switch(pin) {
	case F_PWMB_PIN:
		motor_speed_g = duty;
		FPWM_g.dutyCycle = motor_speed_g;
		Timer_A_outputPWM(TIMER_A0_BASE, &FPWM_g);
		break;
	case B_PWMB_PIN:
		motor_speed_g = duty;
		BPWM_g.dutyCycle = motor_speed_g;
		Timer_A_outputPWM(TIMER_A0_BASE, &BPWM_g);
		break;
	default:
		break;
	}
}

void setDir(botDir dir) {

    // Motor A: Right
    // Motor B: Left
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
