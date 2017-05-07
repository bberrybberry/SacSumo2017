/**
 *
 */
#include "driverlib.h"

#include "motors.h"
#include "reflectance.h"
#include "ir.h"

#define TIMER_PERIOD						511
#define DUTY_CYCLE							350
#define REFLECTANCE_THRESHOLD				3000
#define UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ   16384
#define UCS_MCLK_FLLREF_RATIO   			1000


uint16_t status;
uint16_t randNums[] = {42333, 51850, 37916, 58960, 63947, 63032, 16141, 37571, 63929, 10243};

void setClock(void);
void sensorLedTest(void);
void reflectLedTest(void);
void buttonTest(void);

/**
 * @fn
 * @brief Drive all motors CW
 */
void motorTest(void);

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

	unsigned char count = 0, isFront, isRight, isLeft, notInView, lastSensor;
	uint32_t delay;
	volatile int i;
    //Stop WDT
    WDT_A_hold(WDT_A_BASE);

    //PA.x output
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    //GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);// | GPIO_PIN1 | GPIO_PIN2);
    //GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN4);
    //GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN4);
    //P1REN = 0x10;
    //P1OUT = 0x10;

    setClock();
    //uint32_t clk = UCS_getMCLK();
    Reflectance_init();
    IR_init(IR_SL | IR_SR | IR_FL | IR_FR);
    initSoftwarePWM();
    __bis_SR_register(GIE);
    setSoftwarePWM(48000); // sort of max of 48000

    //GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN1 | GPIO_PIN2);
    //GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN1 | GPIO_PIN2);

    //motorTest();
    motorsInit();
    //GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN1 | GPIO_PIN2);

    setFrontMotorA(CCW);
    setFrontMotorB(CCW);
    setBackMotorA(CCW);
    setBackMotorB(CCW);

    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN2);

    while(1) {

    	delay = 10 * randNums[count % 10];

    	if (Reflectance_getL() > REFLECTANCE_THRESHOLD) {
    		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN2);
    		setDir(RIGHT);
    		for(i = 0; i < delay; i++);
    		setDir(FORWARD);
    	}
    	else if(Reflectance_getR() > REFLECTANCE_THRESHOLD) {
    		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN2);
    		setDir(LEFT);
    		for(i = 0; i < delay; i++);
    		setDir(FORWARD);
    	}
    	else {
    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN1);
    		setDir(FORWARD);
    	}

    	if (IR_getOutput(IR_SL)) {
    		isFront = 0;
    		isRight = 0;
    		isLeft = 1;
    		notInView = 0;
    		lastSensor = IR_SL;
    		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN1);
    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
    	}
    	else if (IR_getOutput(IR_SR)) {
    		isFront = 0;
    		isRight = 1;
    		isLeft = 0;
    		notInView = 0;
    		lastSensor = IR_SR;
    		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN1);
    	}
    	else if (IR_getOutput(IR_FR)) {
    		isFront = 1;
    		isRight = 0;
    		isLeft = 0;
    		notInView = 0;
    		lastSensor = IR_FR;
    		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN1);
    	}
    	else if (IR_getOutput(IR_FL)) {
    		isFront = 1;
    		isRight = 0;
    		isLeft = 0;
    		notInView = 0;
    		lastSensor = IR_FL;
    		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN1);
    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
    	}
    	else {
    		isFront = 0;
    		isRight = 0;
    		isLeft = 0;
    		notInView = 1;
    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN1);
    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
    	}

    	if (isRight) {
    		setDir(RIGHT);
    	}
    	else if (isLeft) {
    		setDir(LEFT);
    	}
    	else if (isFront) {
    		setDir(FORWARD);
    	}
    	else if (notInView) {
    		setDir(FORWARD);
//    		if ((lastSensor & IR_SR) || (lastSensor & IR_FR)) {
//    			setDir(RIGHT);
//    		}
//    		else {
//    			setDir(LEFT);
//    		}
    	}
    	count++;
    }

}

void setClock(void) {
    PMM_setVCore(PMM_CORE_LEVEL_3);

    //Set DCO FLL reference = REFO
    UCS_initClockSignal(
        UCS_FLLREF,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );
    //Set ACLK = REFO
    UCS_initClockSignal(
        UCS_ACLK,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );

    //Set Ratio and Desired MCLK Frequency  and initialize DCO
    UCS_initFLLSettle(
        UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ,
        UCS_MCLK_FLLREF_RATIO
        );

    // Enable global oscillator fault flag
    SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
    SFR_enableInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

    __bis_SR_register(GIE);

    UCSCTL4 &= ~SELS_4;
    UCSCTL4 |= SELS_3;
}

void sensorLedTest(void){
    //TODO: Toggle LED at p8.0 when an IR sensor detects an object
	if (IR_getOutput(IR_FL | IR_FR | IR_SL | IR_SR)) {
		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
	}
	else {
		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
	}
}

void reflectLedTest(void){
    //TODO: Toggle an LED at p8.1 when the reflectance sensor reading reaches a threshold
}

void buttonTest(void){
	//TODO: Toggle LED at p8.2 when the button at p2.4 is pressed
}

void motorTest(void){
    motorsInit();

    setFrontMotorA(CW);
    setFrontMotorB(CW);
    setBackMotorA(CW);
    setBackMotorB(CW);
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMERB0_ISR(void) {
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN1);
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN2);
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMERA0_ISR(void) {
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN1);
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN2);
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=UNMI_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(UNMI_VECTOR)))
#endif
void NMI_ISR(void)
{
    do
    {
        // If it still can't clear the oscillator fault flags after the timeout,
        // trap and wait here.
        status = UCS_clearAllOscFlagsWithTimeout(1000);
    }
    while(status != 0);
}

//    	if (Reflectance_getL() > REFLECTANCE_THRESHOLD) {
//    		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN1);
//    	}
//    	else {
//    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN1);
//    	}
//
//    	if (Reflectance_getR() > REFLECTANCE_THRESHOLD) {
//    		GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
//    	}
//    	else {
//    		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
//    	}
//
//    	//__delay_cycles(1000);

