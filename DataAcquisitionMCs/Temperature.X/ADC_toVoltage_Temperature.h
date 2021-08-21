#ifndef adc_tovoltage_temperature_h
#define adc_tovoltage_temperature_h

#include "mcc_generated_files/include/adc0.h"

#define DAC 0x33 //address for DAC output
#define DACREF 1.028 //DAC configured to 1.024V
#define half_M 32768 //2^16 levels for differential [-3278, 3277]
#define Gain 16 //PGA set to x16


void ADC_SetVREF();
/**
 * \brief compute the reference voltage of the ADC: VDD.
 */

float ADC_GetVREF();
/**
 * \return the previously computed reference
 */

float ADC_DifftoVoltage(bool viaPGA, diff_adc_result_t diffres);
/**
 * \brief function to transform a differential ADC measurement, scaled and with gain 8
 * \return the measured differential voltage
 */

#endif