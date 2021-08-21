#ifndef i2c_pressure_h
#define i2c_pressure_h

#include "mcc_generated_files/include/twi0_slave.h"

float Pt3, Pt4, Pt9, P9;

void read_reg();
/**
 * \brief Read the command sent by the master.
 * reg = 0 means to send the I2C address
 * reg = 0x63 == 'Pt3' send Pt3
 * reg = 0x64 == 'Pt4' send Pt4
 * reg = 0x69 == 'Pt9' send Pt9
 * reg = 0x60 == 'P9' send P9
 */

void write_float();
/**
 * \brief convert type float to bytes
 * do it with Thrust or Flow depending on the reg byte
 */


void send_data();
/**
 * \brief send the data.
 * if reg = 0 just send the address
 * if reg != 0 use the y variable to know which byte to send
 */

void clear();
/**
 * \brief once the Tx is done return the reg and y variables to 0
 * also stop the wait flag so it performs another measurement
 */
#endif