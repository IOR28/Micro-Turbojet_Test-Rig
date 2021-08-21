#ifndef termocouple_h
#define termocouple_h

#include "ADC_toVoltage_Temperature.h"

float measure_Tt(int phase);
//measure the total temperature given the phase at which you want to measure
/**RTD at:
 * Between compressor and combustor: Tt3 -> phase = 3
 */
/**Termocouples at:
 * Bellmouth: Tt1 -> phase = 1
 * Between compressor and combustor: Tt3 -> phase = 3
 * Between combustor and turbine: Tt4 -> phase = 4
 * Nozzle exit: Tt9 -> phase = 9
 */

float compute_Thermocouple();
//read the ADC output, translate it to voltage and compute T using the AD8495 formula
/**AD8495 on Adafruit board: V = T*5mV+1.25 (T in *C)
 * AD8495 on modified Adafruit board (Vref = 0V): V = T*5mV (T in *C, +273 K)
*/

#define REF_CHANNEL 0x06 //negative channel input for the RTD conditioning reference
#define R_PT0 100 //constant of the PT sensor
#define ALPHA 0.385 //ohm/ºC 0.00385*R_PT0 constant of PT sensor
#define OFFSET -8 //mV systematic error of the circuit

float compute_RTD();
//perform a differential measure, translate it to resistance and compute T using the PT100 formula
/** R_PT =  V_mV + OFFSET is calibrated and hardcoded above
 *  R_PT = R_PT0 + ALPHA*T
 */
#endif