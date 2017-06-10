/* ###################################################################
**     Filename    : Events.c
**     Project     : psi3441-project
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-06-04, 15:39, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "ADC.h"
#include "DMA_PDD.h"

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AD1_OnMeasurementComplete (module Events)
**
**     Component   :  AD1 [ADC_LDD]
*/
/*!
**     @brief
**         Called after measurement is done, [Interrupt service/event]
**         is enabled, OnMeasurementComplete event is enabled and ADC
**         device is enabled. See [SetEventMask()] method or [Event
**         mask] property group to enable this event and [Enable]
**         method or [Enabled in init. code] property to enable ADC
**         device. If DMA is enabled , this event is called after the
**         configured number of measurements and DMA transfer is done.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void AD1_OnMeasurementComplete(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
  uint16_t val;
  AD1_GetMeasuredValues(AD1, &val);
  insertRing(UserDataPtr, val);
}

/**
 * DMA_IRQHandler()
 * IRQ Handler for DMA Channel 0.
 * Re-sets BCR register.
 */
void DMA0_IRQHandler()
{
  /* Write your code here ... */
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_0);
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, 0x080000);
}

/**
 * DMA1_IRQHandler()
 * IRQ Handler for DMA Channel 1.
 * Re-sets BCR register.
 */
void DMA1_IRQHandler()
{
  /* Write your code here ... */
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_1);
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, 0x080000);
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif

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
