/*
 * PWM.h
 *
 *  Created on: Jun 6, 2017
 *      Author: Gabriel
 */

#ifndef PWM_H_
#define PWM_H_

extern uint16_t PWMBuffer[64];

extern LDD_TDeviceData* DMAT2;
extern LDD_TDeviceData* TU3;


int TPM0_FixPWM();

#endif /* PWM_H_ */
