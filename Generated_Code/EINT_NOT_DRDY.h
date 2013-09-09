/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : EINT_NOT_DRDY.h
**     Project     : ProcessorExpert
**     Processor   : MKL15Z128VLH4
**     Component   : ExtInt_LDD
**     Version     : Component 02.154, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-09-09, 15:23, # CodeGen: 125
**     Abstract    :
**         This component, "ExtInt_LDD", provide a low level API 
**         for unified access of external interrupts handling
**         across various device designs.
**         The component uses one pin which generates interrupt on 
**         selected edge.
**     Settings    :
**          Component name                                 : EINT_NOT_DRDY
**          Pin                                            : PTD4/LLWU_P14/SPI1_PCS0/UART2_RX/TPM0_CH4
**          Pin signal                                     : NOT_DRDY
**          Generate interrupt on                          : falling edge
**          Interrupt                                      : INT_PORTD
**          Interrupt priority                             : low priority
**          Initialization                                 : 
**            Enabled in init. code                        : no
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnInterrupt                                : Enabled
**          Threshold level                                : 0
**     Contents    :
**         Init    - LDD_TDeviceData* EINT_NOT_DRDY_Init(LDD_TUserData *UserDataPtr);
**         Enable  - void EINT_NOT_DRDY_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable - void EINT_NOT_DRDY_Disable(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file EINT_NOT_DRDY.h
** @version 01.00
** @brief
**         This component, "ExtInt_LDD", provide a low level API 
**         for unified access of external interrupts handling
**         across various device designs.
**         The component uses one pin which generates interrupt on 
**         selected edge.
*/         
/*!
**  @addtogroup EINT_NOT_DRDY_module EINT_NOT_DRDY module documentation
**  @{
*/         

#ifndef __EINT_NOT_DRDY_H
#define __EINT_NOT_DRDY_H

/* MODULE EINT_NOT_DRDY. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "IO_Map.h"
#include "GPIO_PDD.h"
#include "PORT_PDD.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define EINT_NOT_DRDY_PRPH_BASE_ADDRESS  0x400FF0C0U
  
/* Methods configuration constants - generated for all enabled component's methods */
#define EINT_NOT_DRDY_Init_METHOD_ENABLED /*!< Init method of the component EINT_NOT_DRDY is enabled (generated) */
#define EINT_NOT_DRDY_Enable_METHOD_ENABLED /*!< Enable method of the component EINT_NOT_DRDY is enabled (generated) */
#define EINT_NOT_DRDY_Disable_METHOD_ENABLED /*!< Disable method of the component EINT_NOT_DRDY is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define EINT_NOT_DRDY_OnInterrupt_EVENT_ENABLED /*!< OnInterrupt event of the component EINT_NOT_DRDY is enabled (generated) */

/* Definition of implementation constants */
#define EINT_NOT_DRDY_PIN_INDEX 0x04U  /*!< Index of the used pin from the port */
#define EINT_NOT_DRDY_PIN_MASK 0x10U   /*!< Mask of the used pin from the port */
#define EINT_NOT_DRDY_MODULE_BASE_ADDRESS PTD_BASE_PTR /*!< Name of macro used as the base address */
#define EINT_NOT_DRDY_PORTCONTROL_BASE_ADDRESS PORTD_BASE_PTR /*!< Name of macro used as the base address */
#define EINT_NOT_DRDY_IRQ_CONFIG PORT_PDD_INTERRUPT_ON_FALLING /*!< Static IRQ configuration */

/*
** ===================================================================
**     Method      :  EINT_NOT_DRDY_Init (component ExtInt_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* EINT_NOT_DRDY_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  EINT_NOT_DRDY_Enable (component ExtInt_LDD)
*/
/*!
**     @brief
**         Enable the component - the external events are accepted.
**         This method is available only if HW module allows
**         enable/disable of the interrupt.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
*/
/* ===================================================================*/
void EINT_NOT_DRDY_Enable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  EINT_NOT_DRDY_Disable (component ExtInt_LDD)
*/
/*!
**     @brief
**         Disable the component - the external events are not accepted.
**         This method is available only if HW module allows
**         enable/disable of the interrupt.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
*/
/* ===================================================================*/
void EINT_NOT_DRDY_Disable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  EINT_NOT_DRDY_Interrupt (component ExtInt_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/* {Default RTOS Adapter} ISR function prototype */
PE_ISR(EINT_NOT_DRDY_Interrupt);

/* END EINT_NOT_DRDY. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __EINT_NOT_DRDY_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.2 [05.07]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/