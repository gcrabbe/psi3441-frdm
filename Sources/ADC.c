/*
 * ADC.c
 *
 *  Created on: Jun 5, 2017
 *      Author: Gabriel
 */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "ADC.h"

/**
 * uint16_t ADCBuffer[16]
 */
uint16_t ADCBuffer[16] __attribute__ ((aligned (32)));

/**
 * Devices
 */
LDD_TDeviceData* AD1;
LDD_TDeviceData* TU2;


int initRing(struct ring *R, uint16_t *buffer, uint8_t size)
{
	// Struct init
	R->first = 0;
	R->last  = 0;
	R->count = 0;
	R->size  = size;

	// Memory allocation
	if(buffer == NULL)
		return -1;
	R->buffer = buffer;

	return 0;
}

int isRingEmpty(struct ring *R)
{
	return (R->count ? 0 : 1);
}


int isRingFull(struct ring *R)
{
	return (R->count >= R->size ? 1 : 0);
}

int insertRing(struct ring *R, uint16_t item)
{
	if(isRingFull(R))
		return -1;
	R->buffer[R->last] = item;

	R->count++;
	if(++R->last >= R->size)
		R->last = 0;

	return R->last;
}


int removeRing(struct ring *R, uint16_t *item)
{
	if(isRingEmpty(R))
		return -1;
	*item = R->buffer[R->first];

	R->count--;
	if(++R->first >= R->size)
		R->first = 0;

	return R->first;
}
