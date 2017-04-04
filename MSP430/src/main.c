/**
 *
 */
#include "driverlib.h"

#include "motors.h"
//#include "reflectance.h"
//#include "ir.h"

#define TIMER_PERIOD 511
#define DUTY_CYCLE  350

void sensorLedTest();
void sensorLedTest(){
    //TODO: Flash LED when an IR sensor detects an object
}

void reflectLedTest();
void reflectLedTest(){
    //TODO: Flash an LED when the reflectance sensor reading reaches a threshold
}

/**
 * @fn
 * @brief Drive all motors CW
 */
void motorTest();
void motorTest(){
    motorsInit();

    setFrontMotorA(CW);
    setFrontMotorB(CW);
    setBackMotorA(CW);
    setBackMotorB(CW);
}

void main(void)
{
    /* Programming NOTE:
     *
     * This how the programming thing is wired up where the battery
     * is in the upper left corner of the PCB
     *
     * |-----|-----|
     * | GND | RST |
     * |-----|-----|
     * | TST | 3V3 |
     * |-----|-----|
     *
     */

    //Stop WDT
    WDT_A_hold(WDT_A_BASE);

    //PA.x output
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1);

    //Set all PA pins HI
    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1);

//    //P1.3 as PWM output
//  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3);
//
//  //Generate PWM on A0.2 - Timer runs in Up mode
//  Timer_A_outputPWMParam param = {0};
//  param.clockSource = TIMER_A_CLOCKSOURCE_ACLK;//TIMER_A_CLOCKSOURCE_SMCLK;
//  param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
//  param.timerPeriod = TIMER_PERIOD;
//  param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
//  param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
//  param.dutyCycle = DUTY_CYCLE;
//  Timer_A_outputPWM(TIMER_A0_BASE, &param);

    motorTest();

//    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN1|GPIO_PIN3);
//    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN1|GPIO_PIN3);
}
