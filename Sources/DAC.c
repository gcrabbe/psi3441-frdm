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
 * uint16_t DACBuffer[64]
 * Sine wave, 12 bits, right-aligned
 */
const uint16_t DACBuffer[64] __attribute__ ((aligned (128))) = {
	0x800,
	0x8C8,
	0x98F,
	0xA52,
	0xB0F,
	0xBC5,
	0xC71,
	0xD13,
	0xDA8,
	0xE2F,
	0xEA6,
	0xF0E,
	0xF64,
	0xFA7,
	0xFD8,
	0xFF6,
	0xFFF,
	0xFF6,
	0xFD8,
	0xFA7,
	0xF64,
	0xF0E,
	0xEA6,
	0xE2F,
	0xDA8,
	0xD13,
	0xC71,
	0xBC5,
	0xB0F,
	0xA52,
	0x98F,
	0x8C8,
	0x800,
	0x737,
	0x670,
	0x5AD,
	0x4F0,
	0x43A,
	0x38E,
	0x2EC,
	0x257,
	0x1D0,
	0x159,
	0x0F1,
	0x09B,
	0x058,
	0x027,
	0x009,
	0x000,
	0x009,
	0x027,
	0x058,
	0x09B,
	0x0F1,
	0x159,
	0x1D0,
	0x257,
	0x2EC,
	0x38E,
	0x43A,
	0x4F0,
	0x5AD,
	0x670,
	0x737
};

/**
 * Devices
 **/
LDD_TDeviceData* DA1;
LDD_TDeviceData* DMAT1;
LDD_TDeviceData* TU1;
