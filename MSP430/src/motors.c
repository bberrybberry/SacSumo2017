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


