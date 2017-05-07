/*
 * reflectance.h
 *
 *  Created on: Apr 1, 2017
 *      Author: bbhig
 */

#ifndef REFLECTANCE_H_
#define REFLECTANCE_H_

#include "driverlib.h"

void Reflectance_init(void);

uint16_t Reflectance_getL(void);
uint16_t Reflectance_getR(void);



#endif /* REFLECTANCE_H_ */
