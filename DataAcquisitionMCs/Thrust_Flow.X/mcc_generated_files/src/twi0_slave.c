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


#include "../../i2c_ThrustFlow.h"
#include "../include/pin_manager.h"
#include <stdbool.h>

/* I2C Internal API's */
/* Slave */
bool I2C0_SlaveIsAddressInterrupt(void);
bool I2C0_SlaveIsDataInterrupt(void);
bool I2C0_SlaveIsStopInterrupt(void);
void I2C0_SlaveOpen(void);
void I2C0_SlaveClose(void);
bool I2C0_SlaveDIR(void);
char I2C0_SlaveReset(void);
uint8_t I2C0_SlaveRead(void);
char I2C0_SlaveWrite(uint8_t data);
bool I2C0_SlaveIsNack(void);
void I2C0_SlaveSendAck(void);
void I2C0_SlaveSendNack(void);
bool I2C0_SlaveIsBusCollision(void);
bool I2C0_SlaveIsBusError(void);
bool I2C0_SlaveIsTxComplete(void);

// Read Event Interrupt Handlers
void I2C0_ReadCallback(void);
void (*I2C0_ReadInterruptHandler)(void);

// Write Event Interrupt Handlers
void I2C0_WriteCallback(void);
void (*I2C0_WriteInterruptHandler)(void);

// Address Event Interrupt Handlers
void I2C0_AddressCallback(void);
void (*I2C0_AddressInterruptHandler)(void);

// Stop Event Interrupt Handlers
void I2C0_StopCallback(void);
void (*I2C0_StopInterruptHandler)(void);

// Bus Collision Event Interrupt Handlers
void I2C0_CollisionCallback(void);
void (*I2C0_CollisionInterruptHandler)(void);

// Bus Error Event Interrupt Handlers
void I2C0_BusErrorCallback(void);
void (*I2C0_BusErrorInterruptHandler)(void);

uint8_t I2C0_Initialize()
{
    //SDASETUP 4CYC; SDAHOLD OFF; FMPEN disabled; 
    TWI0.CTRLA = 0x00;
    
    //Debug Run
    TWI0.DBGCTRL = 0x00;
    
    //Slave Address
    TWI0.SADDR = 0x00;
    
    //ADDRMASK 10; ADDREN enabled; 
    TWI0.SADDRMASK = 0x15;
    
    //DIEN enabled; APIEN enabled; PIEN disabled; PMEN disabled; SMEN disabled; ENABLE enabled; 
    TWI0.SCTRLA = 0xC1;
    
    //ACKACT ACK; SCMD NOACT; 
    TWI0.SCTRLB = 0x00;
    
    //Slave Data
    TWI0.SDATA = 0x00;
    
    //DIF disabled; APIF disabled; COLL disabled; BUSERR disabled; 
    TWI0.SSTATUS = 0x00;
    
    I2C0_SetWriteCallback(read_reg);
    I2C0_SetReadCallback(send_data);
    I2C0_SetAddressCallback(NULL);
    I2C0_SetStopCallback(I2C0_GotoUnaddressed);
    I2C0_SetCollisionCallback(NULL);
    I2C0_SetBusErrorCallback(NULL);
  
    return 0;
}

void I2C0_Open(void)
{
    I2C0_SlaveOpen();
}

void I2C0_Close(void)
{
    I2C0_SlaveClose();
}

ISR(TWI0_TWIS_vect)
{
    /*
    if (I2C0_SlaveIsBusCollision()) {
        I2C0_CollisionCallback();
        return;
    }

    if (I2C0_SlaveIsBusError()) {
        I2C0_BusErrorCallback();
        return;
    }
     */
    if (I2C0_SlaveIsAddressInterrupt()) {
        I2C0_AddressCallback();
        I2C0_SlaveSendAck();
        if (I2C0_SlaveDIR()) {
            // Master wishes to read from slave
            I2C0_ReadCallback();
        }
        return;
    }
    if (I2C0_SlaveIsDataInterrupt()) {
        if (I2C0_SlaveDIR()) {
            // Master wishes to read from slave
            if (!I2C0_SlaveIsNack()) {
                // Received ACK from master
                I2C0_ReadCallback();
            } else {
                // Received NACK from master
                clear();
                I2C0_GotoUnaddressed();
            }
        } else // Master wishes to write to slave
        {
            I2C0_WriteCallback();
            I2C0_SlaveSendAck();
        }
        return;
    }

    // Check if STOP was received
    if (I2C0_SlaveIsStopInterrupt()) {
        I2C0_StopCallback();
        I2C0_SlaveIsTxComplete(); // To check the status of the transaction
        return;
    }
}


uint8_t I2C0_Read(void)
{
    return I2C0_SlaveRead();
}

void I2C0_Write(uint8_t data)
{
    I2C0_SlaveWrite(data);
}

void I2C0_Enable(void)
{
    I2C0_SlaveOpen();
}

void I2C0_SendAck(void)
{
    I2C0_SlaveSendAck();
}

void I2C0_SendNack(void)
{
    I2C0_SlaveSendNack();
}

void I2C0_GotoUnaddressed(void)
{
    // Reset module
    I2C0_SlaveReset();
}

// Read Event Interrupt Handlers
void I2C0_ReadCallback(void)
{
    if (I2C0_ReadInterruptHandler) {
        I2C0_ReadInterruptHandler();
    }
}

void I2C0_SetReadCallback(TWI0_callback handler)
{
    I2C0_ReadInterruptHandler = handler;
}

// Write Event Interrupt Handlers
void I2C0_WriteCallback(void)
{
    if (I2C0_WriteInterruptHandler) {
        I2C0_WriteInterruptHandler();
    }
}

void I2C0_SetWriteCallback(TWI0_callback handler)
{
    I2C0_WriteInterruptHandler = handler;
}

// Address Event Interrupt Handlers
void I2C0_AddressCallback(void)
{
    if (I2C0_AddressInterruptHandler) {
        I2C0_AddressInterruptHandler();
    }
}

void I2C0_SetAddressCallback(TWI0_callback handler)
{
    I2C0_AddressInterruptHandler = handler;
}

// Stop Event Interrupt Handlers
void I2C0_StopCallback(void)
{
    if (I2C0_StopInterruptHandler) {
        I2C0_StopInterruptHandler();
    }
}

void I2C0_SetStopCallback(TWI0_callback handler)
{
    I2C0_StopInterruptHandler = handler;
}

// Bus Collision Event Interrupt Handlers
void I2C0_CollisionCallback(void)
{
    if (I2C0_CollisionInterruptHandler) {
        I2C0_CollisionInterruptHandler();
    }
}

void I2C0_SetCollisionCallback(TWI0_callback handler)
{
    I2C0_CollisionInterruptHandler = handler;
}

// Bus Error Event Interrupt Handlers
void I2C0_BusErrorCallback(void)
{
    if (I2C0_BusErrorInterruptHandler) {
        I2C0_BusErrorInterruptHandler();
    }
}

void I2C0_SetBusErrorCallback(TWI0_callback handler)
{
    I2C0_BusErrorInterruptHandler = handler;
}


/* Slave Configurations */
void I2C0_SlaveOpen(void)
{
    TWI0.SCTRLA |= TWI_ENABLE_bm;
}

void I2C0_SlaveClose(void)
{
    TWI0.SCTRLA &= ~TWI_ENABLE_bm;
}

bool I2C0_SlaveIsBusCollision(void)
{
    return TWI0.SSTATUS & TWI_COLL_bm;
}

bool I2C0_SlaveIsBusError(void)
{
    return TWI0.SSTATUS & TWI_BUSERR_bm;
}

bool I2C0_SlaveIsAddressInterrupt(void)
{
    return (TWI0.SSTATUS & TWI_APIF_bm) && (TWI0.SSTATUS & TWI_AP_bm);
}

bool I2C0_SlaveIsDataInterrupt(void)
{
    return TWI0.SSTATUS & TWI_DIF_bm;
}

bool I2C0_SlaveIsStopInterrupt(void)
{
    return (TWI0.SSTATUS & TWI_APIF_bm) && (!(TWI0.SSTATUS & TWI_AP_bm));
}

bool I2C0_SlaveDIR(void)
{
    return TWI0.SSTATUS & TWI_DIR_bm;
}

void I2C0_SlaveSendAck(void)
{
    TWI0.SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc;
}

void I2C0_SlaveSendNack(void)
{
    TWI0.SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_COMPTRANS_gc;
}

bool I2C0_SlaveIsNack(void)
{
    return TWI0.SSTATUS & TWI_RXACK_bm;
}

bool I2C0_SlaveIsTxComplete(void)
{
    TWI0.SCTRLB = TWI_SCMD_COMPTRANS_gc;
    return TWI0.SCTRLB;
}

uint8_t I2C0_SlaveRead(void)
{
    return TWI0.SDATA;
}

char I2C0_SlaveWrite(uint8_t data)
{
    TWI0.SDATA = data;
    TWI0.SCTRLB |= TWI_SCMD_RESPONSE_gc;
    return TWI0.SDATA;
}

char I2C0_SlaveReset(void)
{
    TWI0.SSTATUS |= (TWI_DIF_bm | TWI_APIF_bm);
    TWI0.SCTRLB = TWI_SCMD_COMPTRANS_gc;
    return TWI0.SSTATUS;
}