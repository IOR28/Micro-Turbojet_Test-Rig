#ifndef adc_tovoltage_pressure_h
#define adc_tovoltage_pressure_h

#include "mcc_generated_files/include/adc0.h"

#define half_M 32767 //2^16 differential levels for [-32768, 32767]
#define V_REF 2.51 //V ADC reference


float ADC_toVoltage(adc_result_t res);
/**
 * \brief function to transform a single ended ADC measurement, scaled and with gain 1
 * \return the measured voltage
 */

#endif