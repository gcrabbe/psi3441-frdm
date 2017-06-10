/* ###################################################################
**     Filename    : main.c
**     Project     : psi3441-project
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-06-04, 15:39, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "DA1.h"
#include "TU1.h"
#include "TU3.h"
#include "TU2.h"
#include "AD1.h"
#include "TPM0.h"
#include "DMA.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "DMA_PDD.h"
#include "DAC.h"
#include "ADC.h"
#include "PWM.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  /* DMA initialization */
  DMA_Init();

  /* DAC initialization */
  DA1 = DA1_Init(NULL);
  TU1 = TU1_Init(NULL);

  /* ADC initialization */
  struct ring ADCRing;
  initRing(&ADCRing, ADCBuffer, 128);

  AD1 = AD1_Init((LDD_TUserData *) &ADCRing);
  AD1_StartCalibration(AD1);
  TU2 = TU2_Init(NULL);

  while(AD1_GetCalibrationResultStatus(AD1) != ERR_OK);
  LDD_ADC_TSample Ch0 = {0};
  AD1_CreateSampleGroup(AD1, &Ch0, 1);

  /* PWM initialization */
  /* Note: TPM0_Init implementation is buggy */
  TPM0_Init();
  TPM0_FixPWM();
  TU3 = TU3_Init(NULL);

  /* Enable DMA transfers */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE);
  // DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE);

  /* Enable ADC transfers */
  // AD1_StartLoopTriggeredMeasurement(AD1);

  /* Local variables */
  uint8_t i;
  uint16_t res;

  /* Main loop */
  for(;;)
  {
    /* Sinal processing */
    if(!isRingEmpty(&ADCRing))
    {
      i = removeRing(&ADCRing, &res);
      res = res >> 6; /* 16 to 10 bits */
      // PWMBuffer[i] = res;
    }
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
