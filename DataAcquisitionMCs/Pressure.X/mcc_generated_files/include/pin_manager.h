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

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "port.h"

//get/set PB5 aliases
#define PB5_SetHigh() do { PORTB_OUTSET = 0x20; } while(0)
#define PB5_SetLow() do { PORTB_OUTCLR = 0x20; } while(0)
#define PB5_Toggle() do { PORTB_OUTTGL = 0x20; } while(0)
#define PB5_GetValue() (VPORTB.IN & (0x1 << 5))
#define PB5_SetDigitalInput() do { PORTB_DIRCLR = 0x20; } while(0)
#define PB5_SetDigitalOutput() do { PORTB_DIRSET = 0x20; } while(0)
#define PB5_SetPullUp() do { PORTB_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PB5_ResetPullUp() do { PORTB_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PB5_SetInverted() do { PORTB_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define PB5_ResetInverted() do { PORTB_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PB5_DisableInterruptOnChange() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PB5_EnableInterruptForBothEdges() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PB5_EnableInterruptForRisingEdge() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PB5_EnableInterruptForFallingEdge() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PB5_DisableDigitalInputBuffer() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PB5_EnableInterruptForLowLevelSensing() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA3 aliases
#define PA3_SetHigh() do { PORTA_OUTSET = 0x8; } while(0)
#define PA3_SetLow() do { PORTA_OUTCLR = 0x8; } while(0)
#define PA3_Toggle() do { PORTA_OUTTGL = 0x8; } while(0)
#define PA3_GetValue() (VPORTA.IN & (0x1 << 3))
#define PA3_SetDigitalInput() do { PORTA_DIRCLR = 0x8; } while(0)
#define PA3_SetDigitalOutput() do { PORTA_DIRSET = 0x8; } while(0)
#define PA3_SetPullUp() do { PORTA_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA3_ResetPullUp() do { PORTA_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA3_SetInverted() do { PORTA_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define PA3_ResetInverted() do { PORTA_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA3_DisableInterruptOnChange() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA3_EnableInterruptForBothEdges() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA3_EnableInterruptForRisingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA3_EnableInterruptForFallingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA3_DisableDigitalInputBuffer() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA3_EnableInterruptForLowLevelSensing() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA5 aliases
#define PA5_SetHigh() do { PORTA_OUTSET = 0x20; } while(0)
#define PA5_SetLow() do { PORTA_OUTCLR = 0x20; } while(0)
#define PA5_Toggle() do { PORTA_OUTTGL = 0x20; } while(0)
#define PA5_GetValue() (VPORTA.IN & (0x1 << 5))
#define PA5_SetDigitalInput() do { PORTA_DIRCLR = 0x20; } while(0)
#define PA5_SetDigitalOutput() do { PORTA_DIRSET = 0x20; } while(0)
#define PA5_SetPullUp() do { PORTA_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA5_ResetPullUp() do { PORTA_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA5_SetInverted() do { PORTA_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define PA5_ResetInverted() do { PORTA_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA5_DisableInterruptOnChange() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA5_EnableInterruptForBothEdges() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA5_EnableInterruptForRisingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA5_EnableInterruptForFallingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA5_DisableDigitalInputBuffer() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA5_EnableInterruptForLowLevelSensing() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA7 aliases
#define PA7_SetHigh() do { PORTA_OUTSET = 0x80; } while(0)
#define PA7_SetLow() do { PORTA_OUTCLR = 0x80; } while(0)
#define PA7_Toggle() do { PORTA_OUTTGL = 0x80; } while(0)
#define PA7_GetValue() (VPORTA.IN & (0x1 << 7))
#define PA7_SetDigitalInput() do { PORTA_DIRCLR = 0x80; } while(0)
#define PA7_SetDigitalOutput() do { PORTA_DIRSET = 0x80; } while(0)
#define PA7_SetPullUp() do { PORTA_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA7_ResetPullUp() do { PORTA_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA7_SetInverted() do { PORTA_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define PA7_ResetInverted() do { PORTA_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA7_DisableInterruptOnChange() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA7_EnableInterruptForBothEdges() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA7_EnableInterruptForRisingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA7_EnableInterruptForFallingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA7_DisableDigitalInputBuffer() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA7_EnableInterruptForLowLevelSensing() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PB1 aliases
#define PB1_SetHigh() do { PORTB_OUTSET = 0x2; } while(0)
#define PB1_SetLow() do { PORTB_OUTCLR = 0x2; } while(0)
#define PB1_Toggle() do { PORTB_OUTTGL = 0x2; } while(0)
#define PB1_GetValue() (VPORTB.IN & (0x1 << 1))
#define PB1_SetDigitalInput() do { PORTB_DIRCLR = 0x2; } while(0)
#define PB1_SetDigitalOutput() do { PORTB_DIRSET = 0x2; } while(0)
#define PB1_SetPullUp() do { PORTB_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PB1_ResetPullUp() do { PORTB_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PB1_SetInverted() do { PORTB_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define PB1_ResetInverted() do { PORTB_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PB1_DisableInterruptOnChange() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PB1_EnableInterruptForBothEdges() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PB1_EnableInterruptForRisingEdge() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PB1_EnableInterruptForFallingEdge() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PB1_DisableDigitalInputBuffer() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PB1_EnableInterruptForLowLevelSensing() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PB0 aliases
#define PB0_SetHigh() do { PORTB_OUTSET = 0x1; } while(0)
#define PB0_SetLow() do { PORTB_OUTCLR = 0x1; } while(0)
#define PB0_Toggle() do { PORTB_OUTTGL = 0x1; } while(0)
#define PB0_GetValue() (VPORTB.IN & (0x1 << 0))
#define PB0_SetDigitalInput() do { PORTB_DIRCLR = 0x1; } while(0)
#define PB0_SetDigitalOutput() do { PORTB_DIRSET = 0x1; } while(0)
#define PB0_SetPullUp() do { PORTB_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PB0_ResetPullUp() do { PORTB_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PB0_SetInverted() do { PORTB_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define PB0_ResetInverted() do { PORTB_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PB0_DisableInterruptOnChange() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PB0_EnableInterruptForBothEdges() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PB0_EnableInterruptForRisingEdge() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PB0_EnableInterruptForFallingEdge() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PB0_DisableDigitalInputBuffer() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PB0_EnableInterruptForLowLevelSensing() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

void PIN_MANAGER_Initialize();
void PORTB_PB5_DefaultInterruptHandler(void);
void PORTB_PB5_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA3_DefaultInterruptHandler(void);
void PORTA_PA3_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA5_DefaultInterruptHandler(void);
void PORTA_PA5_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA7_DefaultInterruptHandler(void);
void PORTA_PA7_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTB_PB1_DefaultInterruptHandler(void);
void PORTB_PB1_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTB_PB0_DefaultInterruptHandler(void);
void PORTB_PB0_SetInterruptHandler(void (* interruptHandler)(void)) ;
#endif /* PINS_H_INCLUDED */
