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
uint16_t PWMBuffer[64] __attribute__ ((aligned (128)));


/**
 * TPM2_FixPWM
 * Fixes buggy center-aligned PWM implementation
 */
int TPM0_FixPWM()
{
	/* Reset channel mode and clear channel flag */
	TPM0_C1SC = (uint32_t) (TPM_CnSC_CHF_MASK);
	/* Re-set channel default value */
	TPM0_C1V = TPM_CnV_VAL(0x0);

	/* Set center-aligned PWM */
	/* Note: Time between TPMx_CnSC accesses must be respected */
	/* Change TPM_CnSC_ELSA_MASK to TPM_CnSC_ELSB_MASK for inverted polarity */
	TPM0_C1SC = (uint32_t) (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK
			| TPM_CnSC_DMA_MASK);

	return 0;
}

/**
 * Devices
 **/
LDD_TDeviceData* DMAT2;
LDD_TDeviceData* TU3;
