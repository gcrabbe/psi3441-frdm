/*
 * PWM.c
 *
 *  Created on: Jun 6, 2017
 *      Author: Gabriel
 */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"
#include "PWM.h"

/**
 * uint16_t PWMBuffer[64]
 */
uint16_t PWMBuffer[64] __attribute__ ((aligned (128))); /* = {
		0x400,
		0x464,
		0x4C8,
		0x529,
		0x588,
		0x5E3,
		0x639,
		0x68A,
		0x6D4,
		0x718,
		0x753,
		0x787,
		0x7B2,
		0x7D4,
		0x7EC,
		0x7FB,
		0x800,
		0x7FB,
		0x7EC,
		0x7D4,
		0x7B2,
		0x787,
		0x753,
		0x718,
		0x6D4,
		0x68A,
		0x639,
		0x5E3,
		0x588,
		0x529,
		0x4C8,
		0x464,
		0x400,
		0x39C,
		0x338,
		0x2D7,
		0x278,
		0x21D,
		0x1C7,
		0x176,
		0x12C,
		0xE8,
		0xAD,
		0x79,
		0x4E,
		0x2C,
		0x14,
		0x5,
		0x0,
		0x5,
		0x14,
		0x2C,
		0x4E,
		0x79,
		0xAD,
		0xE8,
		0x12C,
		0x176,
		0x1C7,
		0x21D,
		0x278,
		0x2D7,
		0x338,
		0x39C
}; */


/**
 * TPM2_FixPWM
 * Fixes buggy center-aligned PWM implementation
 */
int TPM2_FixPWM()
{
	/* Reset channel mode and clear channel flag */
	TPM2_C0SC = (uint32_t) (TPM_CnSC_CHF_MASK);
	/* Re-set channel value */
	TPM2_C0V = TPM_CnV_VAL(0x0800);

	/* Set center-aligned PWM */
	/* Note: Time between TPM2_C0SC accesses must be respected */
	TPM2_C0SC = (uint32_t) (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);

	return 0;
}

/**
 * Devices
 **/
LDD_TDeviceData* DMACH2;
LDD_TDeviceData* TU3;
