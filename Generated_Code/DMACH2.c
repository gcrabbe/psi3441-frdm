/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : DMACH2.c
**     Project     : psi3441-frdm
**     Processor   : MKL25Z128VLK4
**     Component   : DMAChannel_LDD
**     Version     : Component 01.051, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-06-07, 21:09, # CodeGen: 15
**     Abstract    :
**          This embedded component implements
**          a DMA transfer channel descriptor definition.
**     Settings    :
**          Component name                                 : DMACH2
**          Hardware request                               : Enabled
**            Request source                               : Always_Enabled_slot_61_DMA_Request
**            Request periodic trigger                     : Enabled
**          Channel select                                 : Fixed
**            DMA controller device                        : DMA1
**            Channel                                      : DMA_Channel1
**            Allocate channel                             : yes
**            Arbitration type                             : Fixed
**              Priority                                   : 1
**            Interrupt service                            : Enabled
**              Transfer complete interrupt                : 
**                Interrupt vector                         : INT_DMA1
**                Interrupt priority                       : 2
**          External object declaration                    : (string list)
**          Source transaction settings                    : 
**            Start address                                : PWMBuffer
**            Transaction size                             : 16-bits
**            Address adjustment                           : 2
**            Address modulo                               : 128 Bytes
**          Destination transaction settings               : 
**            Start address                                : 0x4003A010
**            Transaction size                             : 16-bits
**            Address adjustment                           : 0
**            Address modulo                               : Buffer disabled
**          Transfer settings                              : 
**            Auto-align mode                              : Disabled
**            Asynchronous requests                        : Disabled
**            Transaction size                             : 16-bits
**            Transactions count                           : 1
**            Request count                                : 256
**            After request complete actions               : 
**              Channel linking                            : Disabled
**              Address adjustment                         : Disabled
**            After transfer complete actions              : 
**              Disable peripheral request                 : no
**              Channel linking                            : Disabled
**              Address adjustment                         : Disabled
**              Scatter/gather                             : Disabled
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Half complete                                : Disabled
**            Event mask                                   : 
**              OnComplete                                 : Enabled
**              OnError                                    : Enabled
**     Contents    :
**         Init            - LDD_TDeviceData* DMACH2_Init(LDD_TUserData *UserDataPtr);
**         EnableRequest   - LDD_TError DMACH2_EnableRequest(LDD_TDeviceData *DeviceDataPtr);
**         StartTransfer   - LDD_TError DMACH2_StartTransfer(LDD_TDeviceData *DeviceDataPtr);
**         GetError        - LDD_DMA_TErrorFlags DMACH2_GetError(LDD_TDeviceData *DeviceDataPtr);
**         SetRequestCount - LDD_TError DMACH2_SetRequestCount(LDD_TDeviceData *DeviceDataPtr,...
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
** @file DMACH2.c
** @version 01.00
** @brief
**          This embedded component implements
**          a DMA transfer channel descriptor definition.
*/         
/*!
**  @addtogroup DMACH2_module DMACH2 module documentation
**  @{
*/         

/* MODULE DMACH2. */

#include "Events.h"
#include "DMACH2.h"
/* {Default RTOS Adapter} No RTOS includes */

#define DMACH2_INIT_EVENTS_MASK ((LDD_TEventMask)( \
          LDD_DMA_ON_COMPLETE | \
          LDD_DMA_ON_ERROR))

/* This code is generated from External object declaration property */
#include "PWM.h"

/* Channel configuration structure */
DMA1_TChnInit const DMACH2_ChInit = {
  /* Logical channel number */
  DMA1_STATIC_CHANNEL_0,               /* Phy channel: DMA_Channel1 */
  { /* TCD initial settings */
    DMA_SAR_SAR(0x00),                 /* Initial value is not constant expresion. See Init() method to see initial value. */
    DMA_DAR_DAR(0x4003A010),           /* DAR register initial value */
    DMA_DSR_BCR_BCR(0x0200),           /* DSR_BCR register initial value */
    ( DMA_DCR_EINT_MASK |
      DMA_DCR_CS_MASK |
      DMA_DCR_SINC_MASK |
      DMA_DCR_SSIZE(0x02) |
      DMA_DCR_DSIZE(0x02) |
      DMA_DCR_SMOD(0x04) |
      DMA_DCR_DMOD(0x00) |
      DMA_DCR_LINKCC(0x00) |
      DMA_DCR_LCH1(0x00) |
      DMA_DCR_LCH2(0x00)
    )                                  /* DCR register initial value */
  },
  /* DMAMUX initial settings */
  (DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_TRIG_MASK | DMAMUX_CHCFG_SOURCE(0x3D)), /* DMA multiplexor configuration register initial value 'Always_Enabled_slot_61_DMA_Request' */
  { /* Events initial setting */
    &DMACH2_OnComplete,                /* OnComplete callback address */
    &DMACH2_OnError                    /* OnComplete callback address */
  }
};

/*
** ===================================================================
**     Method      :  DMACH2_Init (component DMAChannel_LDD)
*/
/*!
**     @brief
**         Initializes the DMAChannel_LDD component. This method
**         allocates no memory. Memory for all DMA used channles is
**         allocated by DMAController componet .
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* DMACH2_Init(LDD_TUserData *UserDataPtr)
{
  LDD_TDeviceData                 *DevDataPtr; /* DMA device data structure pointer */
  LDD_TDeviceData                 *ChnDevDataPtr; /* DMA channel device data structure pointer */
  DMA1_TChnInit                    ChnInit;

  DevDataPtr = PE_LDD_DeviceDataList[PE_LDD_COMPONENT_DMA1_ID]; /* Get DMA peripheral handle */
  if (DevDataPtr == NULL) {            /* Is DMA peripheral initialized? */
    DevDataPtr = DMA1_Init();          /* No, try to initialize it */
    if (DevDataPtr == NULL) {          /* initialization failed? */
      return NULL;                     /* Yes, return NULL */
    }
  }
  ChnInit = DMACH2_ChInit;             /* Initialize local copy of init. structure */
  ChnInit.TCD.DMA_SAR_Reg = DMA_SAR_SAR(PWMBuffer); /* SAR register initial value */
  /* Initialize DMA channel device and get DMA channel handle */
  ChnDevDataPtr = DMA1_InitChannel(DevDataPtr, (DMA1_TChnInit *)(void *)&ChnInit, UserDataPtr);
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_DMACH2_ID,ChnDevDataPtr);
  /* Return pointer to the channel data structure */
  return (ChnDevDataPtr);
}

/*
** ===================================================================
**     Method      :  DMACH2_EnableRequest (component DMAChannel_LDD)
*/
/*!
**     @brief
**         The method enables request from peripheral. Please note that
**         this method doesn't start the transfer. The transfer is
**         started as soon as DMA request from peripheral is asserted.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK. 
**                           - ERR_DISABLED - Component is disabled.
*/
/* ===================================================================*/
LDD_TError DMACH2_EnableRequest(LDD_TDeviceData *DeviceDataPtr)
{
  return DMA1_EnableRequest((DMA1_TChanDeviceData *)DeviceDataPtr);
}

/*
** ===================================================================
**     Method      :  DMACH2_StartTransfer (component DMAChannel_LDD)
*/
/*!
**     @brief
**         The method starts DMA transfer on the selected DMA channel.
**         This methods initiates explicit SW transfer request. Please
**         note that call of this method if peripheral request is
**         enabled can cause unpredictable behaviour.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK. 
**                           - ERR_DISABLED - Component is disabled.
*/
/* ===================================================================*/
LDD_TError DMACH2_StartTransfer(LDD_TDeviceData *DeviceDataPtr)
{
  return DMA1_StartTransfer((DMA1_TChanDeviceData *)DeviceDataPtr);
}

/*
** ===================================================================
**     Method      :  DMACH2_GetError (component DMAChannel_LDD)
*/
/*!
**     @brief
**         Returns channel error flags and clears these flags. 
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - DMA Error flags.
*/
/* ===================================================================*/
LDD_DMA_TErrorFlags DMACH2_GetError(LDD_TDeviceData *DeviceDataPtr)
{
  return DMA1_GetError((DMA1_TChanDeviceData *)DeviceDataPtr);
}

/*
** ===================================================================
**     Method      :  DMACH2_SetRequestCount (component DMAChannel_LDD)
*/
/*!
**     @brief
**         Sets number of requests required to complete transfer.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         RequestCount    - Number of requests
**                           required to complete transfer.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK. 
**                           - ERR_DISABLED - Component is disabled.
*/
/* ===================================================================*/
LDD_TError DMACH2_SetRequestCount(LDD_TDeviceData *DeviceDataPtr, LDD_DMA_TRequestCount RequestCount)
{
  return DMA1_SetRequestCount((DMA1_TChanDeviceData *)DeviceDataPtr, RequestCount);
}

/* END DMACH2. */

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