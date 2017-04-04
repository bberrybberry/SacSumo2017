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

}


void setSpeed(unsigned char pin, unsigned char duty) {

}

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
