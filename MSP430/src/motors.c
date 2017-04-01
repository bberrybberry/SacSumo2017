/**
 *
 */

#include "motors.h"

void init(){
    //init digital direction inputs
    //PA.x output
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0);

    //Set all PA pins HI
    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);

    //P1.3 as PWM output
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3);



    //init PWM

}
