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
#include "PWM.h"

/**
 * uint16_t PWMBuffer[64]
 */
uint16_t PWMBuffer[64] __attribute__ ((aligned (128)));
