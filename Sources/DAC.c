/*
 * DAC.c
 *
 *  Created on: Jun 4, 2017
 *      Author: Gabriel
 */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "DAC.h"


/**
 * uint16_t DACBuffer[16]
 * Sine wave, 12 bits, right-aligned
 */
const uint16_t DACBuffer[16] __attribute__ ((aligned (32))) = {
		0x0800,
		0x0B10,
		0x0DA8,
		0x0F64,
		0x0FFF,
		0x0F64,
		0x0DA8,
		0x0B10,
		0x0800,
		0x04F0,
		0x0258,
		0x009C,
		0x0000,
		0x009C,
		0x0258,
		0x04F0
};

/**
 * Devices
 **/
LDD_TDeviceData* DA1;
LDD_TDeviceData* DMAT1;
LDD_TDeviceData* TU1;
