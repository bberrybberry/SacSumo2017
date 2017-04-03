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
