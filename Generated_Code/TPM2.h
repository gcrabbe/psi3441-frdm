/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : TPM2.h
**     Project     : psi3441-frdm
**     Processor   : MKL25Z128VLK4
**     Component   : Init_TPM
**     Version     : Component 01.002, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-05-09, 09:43, # CodeGen: 77
**     Abstract    :
**          This file implements the TPM (TPM2) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
**     Settings    :
**          Component name                                 : TPM2
**          Device                                         : TPM2
**          Settings                                       : 
**            Clock gate                                   : Enabled
**            Clock settings                               : 
**              Clock source                               : TPM counter clock
**              Prescaler                                  : divide by 128
**              Counter frequency                          : 187.500 kHz
**              Modulo counter                             : 6249
**              Period                                     : 33.333 ms
**            DBG mode                                     : TPM counter stopped; output pins remain the same
**            Global time base                             : Disabled
**            Counter reload on trigger                    : Disabled
**            Counter start on trigger                     : Disabled
**            Counter stop on overflow                     : Disabled
**            Counter in Doze mode                         : Enabled
**          Channels                                       : 
**            Channel 0                                    : Disabled
**            Channel 1                                    : Disabled
**          Pins                                           : 
**            External clock pin                           : Disabled
**            HW Synchronization trigger                   : Disabled
**          Interrupts                                     : 
**            Channels / Timer overflow / Fault            : 
**              Interrupt                                  : INT_TPM2
**              Interrupt request                          : Disabled
**              Interrupt priority                         : 0 (Highest)
**              ISR Name                                   : 
**              Channels interrupt/DMA                     : See the respective Channel settings
**              Timer overflow DMA                         : Disabled
**              Timer overflow interrupt                   : Disabled
**          Initialization                                 : 
**            Call Init method                             : yes
**     Contents    :
**         Init - void TPM2_Init(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file TPM2.h
** @version 01.02
** @brief
**          This file implements the TPM (TPM2) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
*/         
/*!
**  @addtogroup TPM2_module TPM2 module documentation
**  @{
*/         

#ifndef TPM2_H_
#define TPM2_H_

/* MODULE TPM2. */

/* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

/* Peripheral base address parameter */
#define TPM2_DEVICE TPM2_BASE_PTR


/*
** ===================================================================
**     Method      :  TPM2_Init (component Init_TPM)
**     Description :
**         This method initializes registers of the TPM module
**         according to the Peripheral Initialization settings.
**         Call this method in user code to initialize the module. By
**         default, the method is called by PE automatically; see "Call
**         Init method" property of the component for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TPM2_Init(void);


/* END TPM2. */
#endif /* #ifndef __TPM2_H_ */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
