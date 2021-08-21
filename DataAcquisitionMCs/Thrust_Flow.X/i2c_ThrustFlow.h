#ifndef i2c_ThrustFlow_h
#define i2c_ThrustFlow_h

#include "mcc_generated_files/include/twi0_slave.h"

float Thrust, Flow;

void read_reg();
/**
 * \brief Read the command sent by the master.
 * reg = 0 means to send the I2C address
 * reg = 0x54 == 'T' send thrust
 * reg = 0x46 == 'F' send flow
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