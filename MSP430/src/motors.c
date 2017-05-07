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
    timer_period_g = 65;
    motor_speed_g = 10;
    //P1.1-4 as PWM output
    /*
     * Last minute corrections:
     *
     * Some PWM signals got screwy, so now each driver gets the same signal to
     * PWMA and PWMB shorted acrossed the test points at the top of the board.
     */
    //GPIO_setAsPeripheralModuleFunctionOutputPin(PWM_PORT, B_PWMB_PIN);
    //GPIO_setAsInputPin(PWM_PORT, F_PWMA_PIN | B_PWMA_PIN);

    //Generate PWM on A0.1 - Timer runs in Up mode
//    Timer_A_outputPWMParam FPWM_A = {0};
//    Timer_A_outputPWMParam FPWM_B = {0};
//    FPWM_B.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
//    FPWM_B.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
//    FPWM_B.timerPeriod = timer_period_g;
//    FPWM_B.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
//    FPWM_B.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
//    FPWM_B.dutyCycle = motor_speed_g;
//    Timer_A_outputPWM(TIMER_A0_BASE, &FPWM_B);

    //Timer_A_outputPWMParam FPWM_B = {0};
//    FPWM_A.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
//    FPWM_A.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
//    FPWM_A.timerPeriod = timer_period_g;
//    FPWM_A.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
//    FPWM_A.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
//    FPWM_A.dutyCycle = motor_speed_g;
//    Timer_A_outputPWM(TIMER_A0_BASE, &FPWM_A);

//    Timer_A_outputPWMParam BPWM_A = {0};
//    BPWM_A.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
//    BPWM_A.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
//    BPWM_A.timerPeriod = timer_period_g;
//    BPWM_A.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
//    BPWM_A.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
//    BPWM_A.dutyCycle = motor_speed_g;
//    Timer_A_outputPWM(TIMER_A0_BASE, &BPWM_A);
//
    //Generate PWM on A0.3 - Timer runs in Up mode
//    Timer_A_outputPWMParam BPWM_B = {0};
//    BPWM_B.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
//    BPWM_B.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
//    BPWM_B.timerPeriod = timer_period_g;
//    BPWM_B.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
//    BPWM_B.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
//    BPWM_B.dutyCycle = motor_speed_g;
//    Timer_A_outputPWM(TIMER_A0_BASE, &BPWM_B);

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
	    setFrontMotorB(CCW);
	    setBackMotorA(CW);
	    setBackMotorB(CCW);
		break;
	case RIGHT:
	    setFrontMotorA(CCW);
	    setFrontMotorB(CW);
	    setBackMotorA(CCW);
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

void initSoftwarePWM() {

	GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN1 | GPIO_PIN2);

    Timer_A_initContinuousModeParam initContParam1 = {0};
    initContParam1.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    initContParam1.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    initContParam1.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initContParam1.timerClear = TIMER_A_DO_CLEAR;
    initContParam1.startTimer = false;
    Timer_A_initContinuousMode(TIMER_A1_BASE, &initContParam1);

    //Initialize compare mode
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
                                         TIMER_A_CAPTURECOMPARE_REGISTER_0
                                         );

    Timer_A_initCompareModeParam initCompParam1 = {0};
    initCompParam1.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    initCompParam1.compareInterruptEnable =
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initCompParam1.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    initCompParam1.compareValue = INITIAL_DUTY;
    Timer_A_initCompareMode(TIMER_A1_BASE, &initCompParam1);

	Timer_B_initContinuousModeParam initContParam2 = {0};
	initContParam2.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;
	initContParam2.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_1;
	initContParam2.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_DISABLE;
	initContParam2.timerClear = TIMER_B_DO_CLEAR;
	initContParam2.startTimer = false;
	Timer_B_initContinuousMode(TIMER_B0_BASE, &initContParam2);

	//Initialize compare mode
	Timer_B_clearCaptureCompareInterrupt(TIMER_B0_BASE,
										 TIMER_B_CAPTURECOMPARE_REGISTER_0);

	Timer_B_initCompareModeParam initCompParam2 = {0};
	initCompParam2.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_0;
	initCompParam2.compareInterruptEnable =
		TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE;
	initCompParam2.compareOutputMode = TIMER_B_OUTPUTMODE_OUTBITVALUE;
	initCompParam2.compareValue = TWO_MS_COUNT;
	Timer_B_initCompareMode(TIMER_B0_BASE, &initCompParam2);

    Timer_A_startCounter(TIMER_A1_BASE,
                         TIMER_A_CONTINUOUS_MODE
                         );

	Timer_B_startCounter(TIMER_B0_BASE,
						 TIMER_B_CONTINUOUS_MODE
						 );

	//__bis_SR_register(GIE);

}

void setSoftwarePWM(uint16_t duty) {
	Timer_A_setCompareValue(TIMER_A1_BASE,
							TIMER_A_CAPTURECOMPARE_REGISTER_0,
							duty
							);
}
