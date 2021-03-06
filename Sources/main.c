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
#include "TPM1.h"
#include "TPM2.h"
#include "DA1.h"
#include "AD1.h"
#include "TPM0.h"
#include "DMA.h"
#include "PTD.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "DAC.h"
#include "ADC.h"
#include "PWM.h"
#include "DMA_PDD.h"
#include "GPIO_PDD.h"
#include "PORT_PDD.h"

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
  DA1_Init(NULL);
  TPM1_Init();

  /* ADC initialization */
  struct ring ADCRing;
  initRing(&ADCRing, ADCBuffer, 16);

  AD1 = AD1_Init((LDD_TUserData *) &ADCRing);
  AD1_StartCalibration(AD1);
  TPM2_Init();

  while(AD1_GetCalibrationResultStatus(AD1) != ERR_OK);
  initRing(&ADCRing, ADCBuffer, 64); /* Discard calibration readings */

  LDD_ADC_TSample Ch0 = {0};
  AD1_CreateSampleGroup(AD1, &Ch0, 1);

  /* PWM initialization */
  /* Note: TPM0_Init implementation is buggy */
  TPM0_Init();
  TPM0_FixPWM();

  /* GPIO initialization */
  PTD_Init();
  PORT_PDD_SetPinMuxControl(PORTD_BASE_PTR, 3, PORT_PDD_MUX_CONTROL_ALT1);

  /* Enable DAC transfers */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE);

  /* Enable ADC transfers */
  AD1_StartLoopTriggeredMeasurement(AD1);

  /* Enable PWM transfers */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE);

  /* Local variables */
  uint8_t i;
  uint16_t res;

  /* Main loop */
  for(;;)
  {
    /* Sinal processing */
    if(!isRingEmpty(&ADCRing))
    {
      /* Set FoM */
      GPIO_PDD_SetPortDataOutput(PTD_BASE_PTR, 0x8);

      /* Read from input buffer */
      i = removeRing(&ADCRing, &res);

      /* Signal processing */
      /* At this time, only word size conversion is effected.
       * No suitable FIR has been found that respects both performance and delay
       * constraints. */
      res = res >> 8; /* 16 to 8 bits */

      /* Phase delay */
      /* The phase delay is nominally 120 degrees (21.33 samples).
       * Note that 1 sample is always lost, as the PWM register is written on the next trigger event. */
      i += 20;   /* 20+1 = 21 sample delay */
      i &= 0x3F; /* Output index modulo 64 */

      /* Write to output buffer */
      PWMBuffer[i] = res;

      /* Reset FoM */
      GPIO_PDD_SetPortDataOutput(PTD_BASE_PTR, 0x0);
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
