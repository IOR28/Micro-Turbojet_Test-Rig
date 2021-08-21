/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/


#include "../include/tcb0.h"


/**
 * \brief Initialize tcb interface
 *
 * \return Initialization status.
 */
int8_t TCB0_Initialize()
{
    //Compare or Capture
    TCB0.CCMP = 0x00;

    //Count
    TCB0.CNT = 0x00;

    //ASYNC disabled; CCMPINIT disabled; CCMPEN disabled; CNTMODE FRQ; 
    TCB0.CTRLB = 0x03;

    //DBGRUN disabled; 
    TCB0.DBGCTRL = 0x00;

    //FILTER disabled; EDGE disabled; CAPTEI enabled; 
    TCB0.EVCTRL = 0x01;

    //OVF disabled; CAPT disabled; 
    TCB0.INTCTRL = 0x00;

    //OVF disabled; CAPT disabled; 
    TCB0.INTFLAGS = 0x00;

    //Temporary Value
    TCB0.TEMP = 0x00;

    //RUNSTDBY disabled; CASCADE disabled; SYNCUPD disabled; CLKSEL TCA0; ENABLE enabled; 
    TCB0.CTRLA = 0x05;

    return 0;
}

void TCB0_WriteTimer(uint16_t timerVal)
{
    TCB0.CNT=timerVal;
}

uint16_t TCB0_ReadTimer(void)
{
    uint16_t readVal;

    readVal = TCB0.CNT;

    return readVal;
}

void TCB0_EnableCaptInterrupt(void)
{
    TCB0.INTCTRL |= TCB_CAPT_bm; /* Capture or Timeout: enabled */
}

void TCB0_EnableOvfInterrupt(void)
{
	TCB0.INTCTRL |= TCB_OVF_bm; /* Overflow Interrupt: enabled */
}

void TCB0_DisableCaptInterrupt(void)
{
    TCB0.INTCTRL &= ~TCB_CAPT_bm; /* Capture or Timeout: disabled */
}

void TCB0_DisableOvfInterrupt(void)
{
	TCB0.INTCTRL &= ~TCB_OVF_bm; /* Overflow Interrupt: disabled */

}

inline void TCB0_ClearCaptInterruptFlag(void)
{
    TCB0.INTFLAGS &= ~TCB_CAPT_bm;

}

inline void TCB0_ClearOvfInterruptFlag(void)
{
    TCB0.INTFLAGS &= ~TCB_OVF_bm;

}

inline bool TCB0_IsCaptInterruptEnabled(void)
{
    return ((TCB0.INTCTRL & TCB_CAPT_bm) > 0);
}

inline bool TCB0_IsOvfInterruptEnabled(void)
{
    return ((TCB0.INTCTRL & TCB_OVF_bm) > 0);
}


