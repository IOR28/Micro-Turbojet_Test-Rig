#ifndef transducer_h
#define transducer_h

#include "ADC_toVoltage_Pressure.h"

float measure_Pt(int phase);
//measure the total pressure given the phase at which you want to measure
/**Transducers at:
 * Between compressor and combustor: Pt3 -> phase = 3
 * Between combustor and turbine: Pt4 -> phase = 4
 * Nozzle output: Pt9 -> phase = 9
 * Nozzle output, static pressure(+1): P9 -> phase = 10
 */


float compute_P();
//read the ADC output, translate it to voltage and compute P.
/**Transducers have output 4 to 20mA, connected to a 120ohm resistor and two 
 * possible Full Scales: 2.5bar and 4bar.
 * V (mV) = I*R, I = (20-4)/(FS-0) * P + 4
 * P = (V/R-4) * FS/16 (P in bar, *10^5 Pa)
 */

#endif