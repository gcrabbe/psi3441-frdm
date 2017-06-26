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
 * uint16_t PWMBuffer[16]
 */
uint16_t PWMBuffer[16] __attribute__ ((aligned (32)));


/**
 * TPM2_FixPWM
 * Fixes buggy center-aligned PWM implementation
 */
int TPM0_FixPWM()
{
	/* Reset channel mode and clear channel flag */
	TPM0_C1SC = (uint32_t) (TPM_CnSC_CHF_MASK);
	/* Re-set channel default value */
	TPM0_C1V = TPM_CnV_VAL(0x03FF);

	/* Set center-aligned PWM */
	/* Note: Time between TPMx_CnSC accesses must be respected */
	TPM0_C1SC = (uint32_t) (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK
			| TPM_CnSC_DMA_MASK);

	return 0;
}

/**
 * Devices
 **/
LDD_TDeviceData* DMAT2;
LDD_TDeviceData* TU3;
