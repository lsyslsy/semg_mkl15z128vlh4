/* ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MKL15Z128VLH4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-12-23, 01:18, # CodeGen: 172
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         DMAT_S_SPI_RX_OnComplete  - void DMAT_S_SPI_RX_OnComplete(LDD_TUserData *UserDataPtr);
**         DMAT_S_SPI_RX_OnError     - void DMAT_S_SPI_RX_OnError(LDD_TUserData *UserDataPtr);
**         DMAT_S_SPI_TX_OnComplete  - void DMAT_S_SPI_TX_OnComplete(LDD_TUserData *UserDataPtr);
**         DMAT_S_SPI_TX_OnError     - void DMAT_S_SPI_TX_OnError(LDD_TUserData *UserDataPtr);
**         DMAT_M_SPI_RX_OnComplete  - void DMAT_M_SPI_RX_OnComplete(LDD_TUserData *UserDataPtr);
**         DMAT_M_SPI_RX_OnError     - void DMAT_M_SPI_RX_OnError(LDD_TUserData *UserDataPtr);
**         DMAT_M_SPI_TX_OnComplete  - void DMAT_M_SPI_TX_OnComplete(LDD_TUserData *UserDataPtr);
**         DMAT_M_SPI_TX_OnError     - void DMAT_M_SPI_TX_OnError(LDD_TUserData *UserDataPtr);
**         EINT_SYNC_INT_OnInterrupt - void EINT_SYNC_INT_OnInterrupt(LDD_TUserData *UserDataPtr);
**         EINT_NOT_DRDY_OnInterrupt - void EINT_NOT_DRDY_OnInterrupt(LDD_TUserData *UserDataPtr);
**         SS_SPI0_OnBlockSent       - void SS_SPI0_OnBlockSent(LDD_TUserData *UserDataPtr);
**         SS_SPI0_OnBlockReceived   - void SS_SPI0_OnBlockReceived(LDD_TUserData *UserDataPtr);
**         SM_SPI1_OnBlockSent       - void SM_SPI1_OnBlockSent(LDD_TUserData *UserDataPtr);
**         SM_SPI1_OnBlockReceived   - void SM_SPI1_OnBlockReceived(LDD_TUserData *UserDataPtr);
**         Cpu_OnNMIINT              - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "SM_SPI1.h"
#include "SS_SPI0.h"
#include "CsIO_UART2.h"
#include "IO2.h"
#include "SysTick.h"
#include "BitIO_NOT_PWDN.h"
#include "BitIO_NOT_RESET.h"
#include "BitIO_START.h"
#include "BitIO_DAISY_IN.h"
#include "BitIO_UPRDY.h"
#include "BitIO_CLKSEL.h"
#include "EINT_NOT_DRDY.h"
#include "EINT_SYNC_INT.h"
#include "DMAT_M_SPI_TX.h"
#include "DMA_CTRL.h"
#include "DMAT_M_SPI_RX.h"
#include "DMAT_S_SPI_TX.h"
#include "DMAT_S_SPI_RX.h"
#include "WaitTimer.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  DMAT_S_SPI_RX_OnComplete (module Events)
**
**     Component   :  DMAT_S_SPI_RX [DMATransfer_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is anabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**         This event is enabled only if Interrupts property in Channel
**         select section is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMAT_S_SPI_RX_OnComplete(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DMAT_S_SPI_RX_OnError (module Events)
**
**     Component   :  DMAT_S_SPI_RX [DMATransfer_LDD]
*/
/*!
**     @brief
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled only if Interrupts property in Channel select
**         section is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMAT_S_SPI_RX_OnError(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DMAT_S_SPI_TX_OnComplete (module Events)
**
**     Component   :  DMAT_S_SPI_TX [DMATransfer_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is anabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**         This event is enabled only if Interrupts property in Channel
**         select section is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMAT_S_SPI_TX_OnComplete(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DMAT_S_SPI_TX_OnError (module Events)
**
**     Component   :  DMAT_S_SPI_TX [DMATransfer_LDD]
*/
/*!
**     @brief
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled only if Interrupts property in Channel select
**         section is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMAT_S_SPI_TX_OnError(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DMAT_M_SPI_RX_OnComplete (module Events)
**
**     Component   :  DMAT_M_SPI_RX [DMATransfer_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is anabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**         This event is enabled only if Interrupts property in Channel
**         select section is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMAT_M_SPI_RX_OnComplete(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DMAT_M_SPI_RX_OnError (module Events)
**
**     Component   :  DMAT_M_SPI_RX [DMATransfer_LDD]
*/
/*!
**     @brief
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled only if Interrupts property in Channel select
**         section is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMAT_M_SPI_RX_OnError(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DMAT_M_SPI_TX_OnComplete (module Events)
**
**     Component   :  DMAT_M_SPI_TX [DMATransfer_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is anabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**         This event is enabled only if Interrupts property in Channel
**         select section is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMAT_M_SPI_TX_OnComplete(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DMAT_M_SPI_TX_OnError (module Events)
**
**     Component   :  DMAT_M_SPI_TX [DMATransfer_LDD]
*/
/*!
**     @brief
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled only if Interrupts property in Channel select
**         section is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMAT_M_SPI_TX_OnError(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  EINT_SYNC_INT_OnInterrupt (module Events)
**
**     Component   :  EINT_SYNC_INT [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EINT_SYNC_INT_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  EINT_NOT_DRDY_OnInterrupt (module Events)
**
**     Component   :  EINT_NOT_DRDY [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EINT_NOT_DRDY_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  SS_SPI0_OnBlockSent (module Events)
**
**     Component   :  SS_SPI0 [SPISlave_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SS_SPI0_OnBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  SS_SPI0_OnBlockReceived (module Events)
**
**     Component   :  SS_SPI0 [SPISlave_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer. This method is available only if
**         the ReceiveBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SS_SPI0_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  SM_SPI1_OnBlockSent (module Events)
**
**     Component   :  SM_SPI1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM_SPI1_OnBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  SM_SPI1_OnBlockReceived (module Events)
**
**     Component   :  SM_SPI1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer. This method is available only if
**         the ReceiveBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM_SPI1_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL15Z128LH4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  WaitTimer_OnCounterRestart (module Events)
**
**     Component   :  WaitTimer [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void WaitTimer_OnCounterRestart(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
