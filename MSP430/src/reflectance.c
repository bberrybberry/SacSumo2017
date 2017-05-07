/*
 * reflectance.c
 *
 *  Created on: Apr 1, 2017
 *      Author: Katherine
 */
#include "reflectance.h"
void Reflectance_init(){
	GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN1);
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN1);

	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0 | GPIO_PIN1);

	ADC12_A_init(ADC12_A_BASE,
				 ADC12_A_SAMPLEHOLDSOURCE_SC,
				 ADC12_A_CLOCKSOURCE_ADC12OSC,
				 ADC12_A_CLOCKDIVIDER_1
				 );

	ADC12_A_enable(ADC12_A_BASE);

	ADC12_A_setupSamplingTimer(ADC12_A_BASE,
							   ADC12_A_CYCLEHOLD_256_CYCLES,
							   ADC12_A_CYCLEHOLD_4_CYCLES,
							   ADC12_A_MULTIPLESAMPLESENABLE);

	ADC12_A_configureMemoryParam param0 = {0};
	param0.memoryBufferControlIndex = ADC12_A_MEMORY_0;
	param0.inputSourceSelect = ADC12_A_INPUT_A0;
	param0.positiveRefVoltageSourceSelect = ADC12_A_VREFPOS_AVCC;
	param0.negativeRefVoltageSourceSelect = ADC12_A_VREFNEG_AVSS;
	param0.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
	ADC12_A_configureMemory(ADC12_A_BASE,&param0);

	ADC12_A_configureMemoryParam param1 = {0};
	param1.memoryBufferControlIndex = ADC12_A_MEMORY_1;
	param1.inputSourceSelect = ADC12_A_INPUT_A1;
	param1.positiveRefVoltageSourceSelect = ADC12_A_VREFPOS_AVCC;
	param1.negativeRefVoltageSourceSelect = ADC12_A_VREFNEG_AVSS;
	param1.endOfSequence = ADC12_A_ENDOFSEQUENCE;
	ADC12_A_configureMemory(ADC12_A_BASE,&param1);

	ADC12_A_clearInterrupt(ADC12_A_BASE,
						   ADC12IFG1);

	ADC12_A_startConversion(ADC12_A_BASE,
							ADC12_A_MEMORY_0,
							ADC12_A_REPEATED_SEQOFCHANNELS);

	__bis_SR_register(GIE);
}

uint16_t Reflectance_getL(void){
	return ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_1) & 0x0FFF;
}


uint16_t Reflectance_getR(void){
	return ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_0) & 0x0FFF;
}
