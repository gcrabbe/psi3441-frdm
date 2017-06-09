/*
 * PWM.h
 *
 *  Created on: Jun 6, 2017
 *      Author: Gabriel
 */

#ifndef PWM_H_
#define PWM_H_

extern uint16_t PWMBuffer[128];

extern LDD_TDeviceData* DMACH2;
extern LDD_TDeviceData* TU3;


int TPM2_FixPWM();

#endif /* PWM_H_ */
