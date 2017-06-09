/*
 * ADC.h
 *
 *  Created on: Jun 5, 2017
 *      Author: Gabriel
 */

#ifndef ADC_H_
#define ADC_H_

struct ring
{
	uint16_t *buffer;
	uint8_t first, last;
	uint8_t count, size;
};

extern uint16_t ADCBuffer[128];

extern LDD_TDeviceData* AD1;
extern LDD_TDeviceData* TU2;


int initRing(struct ring *R, uint16_t *buffer, uint8_t size);
int isRingEmpty(struct ring *R);
int isRingFull(struct ring *R);
int insertRing(struct ring *R, uint16_t item);
int removeRing(struct ring *R, uint16_t *item);

#endif /* ADC_H_ */
