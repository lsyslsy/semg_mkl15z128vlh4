/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : WaitTimer.c
**     Project     : ProcessorExpert
**     Processor   : MKL15Z128VLH4
**     Component   : TimerUnit_LDD
**     Version     : Component 01.158, Driver 01.11, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-03-05, 18:21, # CodeGen: 179
**     Abstract    :
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
**     Settings    :
**          Component name                                 : WaitTimer
**          Module name                                    : PIT
**          Counter                                        : PIT_CVAL0
**          Counter direction                              : Down
**          Counter width                                  : 32 bits
**          Value type                                     : Optimal
**          Input clock source                             : Internal
**            Counter frequency                            : 24 MHz
**          Counter restart                                : On-match
**            Period device                                : PIT_LDVAL0
**            Period                                       : 10 ms
**            Interrupt                                    : Enabled
**              Interrupt                                  : INT_PIT
**              Interrupt priority                         : medium priority
**          Channel list                                   : 0
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnCounterRestart                           : Enabled
**              OnChannel0                                 : Disabled
**              OnChannel1                                 : Disabled
**              OnChannel2                                 : Disabled
**              OnChannel3                                 : Disabled
**              OnChannel4                                 : Disabled
**              OnChannel5                                 : Disabled
**              OnChannel6                                 : Disabled
**              OnChannel7                                 : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init           - LDD_TDeviceData* WaitTimer_Init(LDD_TUserData *UserDataPtr);
**         Enable         - LDD_TError WaitTimer_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable        - LDD_TError WaitTimer_Disable(LDD_TDeviceData *DeviceDataPtr);
**         SetPeriodTicks - LDD_TError WaitTimer_SetPeriodTicks(LDD_TDeviceData *DeviceDataPtr,...
**         ResetCounter   - LDD_TError WaitTimer_ResetCounter(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file WaitTimer.c
** @version 01.11
** @brief
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
*/         
/*!
**  @addtogroup WaitTimer_module WaitTimer module documentation
**  @{
*/         

/* MODULE WaitTimer. */

#include "Events.h"
#include "WaitTimer.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 


typedef struct {
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} WaitTimer_TDeviceData;

typedef WaitTimer_TDeviceData *WaitTimer_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static WaitTimer_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static WaitTimer_TDeviceDataPtr INT_PIT__DEFAULT_RTOS_ISRPARAM;

#define AVAILABLE_EVENTS_MASK (LDD_TEventMask)(LDD_TIMERUNIT_ON_COUNTER_RESTART)

/* Internal method prototypes */
/*
** ===================================================================
**     Method      :  WaitTimer_Init (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* WaitTimer_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  WaitTimer_TDeviceData *DeviceDataPrv;
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_PIT__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* SIM_SCGC6: PIT=1 */
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;                                   
  /* PIT_MCR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,MDIS=0,FRZ=0 */
  PIT_MCR = 0x00U;                     /* Enable device clock */
  /* PIT_TCTRL0: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHN=0,TIE=0,TEN=0 */
  PIT_TCTRL0 = 0x00U;                  /* Clear control register */
  /* PIT_TFLG0: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TIF=1 */
  PIT_TFLG0 = PIT_TFLG_TIF_MASK;       /* Clear timer flag register */
  /* PIT_LDVAL0: TSV=0x0003A97F */
  PIT_LDVAL0 = PIT_LDVAL_TSV(0x0003A97F); /* Set up load register */
  /* NVIC_IPR5: PRI_22=0x80 */
  NVIC_IPR5 = (uint32_t)((NVIC_IPR5 & (uint32_t)~(uint32_t)(
               NVIC_IP_PRI_22(0x7F)
              )) | (uint32_t)(
               NVIC_IP_PRI_22(0x80)
              ));                                  
  /* NVIC_ISER: SETENA|=0x00400000 */
  NVIC_ISER |= NVIC_ISER_SETENA(0x00400000);                                   
  /* PIT_TCTRL0: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHN=0,TIE=1,TEN=1 */
  PIT_TCTRL0 = (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK); /* Set up control register */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_WaitTimer_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  WaitTimer_Enable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Enables the component - it starts the signal generation.
**         Events may be generated (see SetEventMask). The method is
**         not available if the counter can't be disabled/enabled by HW.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError WaitTimer_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  PIT_PDD_EnableDevice(PIT_BASE_PTR, PIT_PDD_CHANNEL_0, PDD_ENABLE); /* Enable the device */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  WaitTimer_Disable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Disables the component - it stops signal generation and
**         events calling. The method is not available if the counter
**         can't be disabled/enabled by HW.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError WaitTimer_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  PIT_PDD_EnableDevice(PIT_BASE_PTR, PIT_PDD_CHANNEL_0, PDD_DISABLE);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  WaitTimer_SetPeriodTicks (component TimerUnit_LDD)
*/
/*!
**     @brief
**         The method sets timer re-initialization period (in timer
**         ticks). This method is available only if the property
**         ["Counter restart"] is switched to 'on-match' value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Ticks           - Number of counter ticks before counter
**                           re-initialization. Value 0 means maximal
**                           period value the same as "free-running
**                           mode", e.g. counter overflow or underflow
**                           without any explicit re-initialization.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_PARAM_TICKS - Ticks parameter is out of
**                           possible range.
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError WaitTimer_SetPeriodTicks(LDD_TDeviceData *DeviceDataPtr, WaitTimer_TValueType Ticks)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  PIT_PDD_WriteLoadReg(PIT_BASE_PTR, PIT_PDD_CHANNEL_0, (uint32_t)(Ticks-1));
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  WaitTimer_ResetCounter (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Resets counter. If counter is counting up then it is set to
**         zero. If counter is counting down then counter is updated to
**         the reload value.
**         The method is not available if HW doesn't allow resetting of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError WaitTimer_ResetCounter(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  if ((PIT_PDD_GetEnableDeviceStatus(PIT_BASE_PTR, PIT_PDD_CHANNEL_0)) != 0U) {
    PIT_PDD_EnableDevice(PIT_BASE_PTR, PIT_PDD_CHANNEL_0, PDD_DISABLE);
    PIT_PDD_EnableDevice(PIT_BASE_PTR, PIT_PDD_CHANNEL_0, PDD_ENABLE);
  }
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  WaitTimer_Interrupt (component TimerUnit_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(WaitTimer_Interrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  WaitTimer_TDeviceDataPtr DeviceDataPrv = INT_PIT__DEFAULT_RTOS_ISRPARAM;

  PIT_PDD_ClearInterruptFlag(PIT_BASE_PTR, PIT_PDD_CHANNEL_0); /* Clear interrupt flag */
  WaitTimer_OnCounterRestart(DeviceDataPrv->UserDataPtr); /* Invoke OnCounterRestart event */
}

/* END WaitTimer. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/