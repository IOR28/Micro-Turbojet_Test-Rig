#ifndef loadcell_h
#define loadcell_h

#include <../../../avr/avr/include/stdint.h>

#define DAC 0x33 //address for DAC output
#define DACREF 1.024 //DAC configured to 1.024V
#define half_M 32768 //2^16 levels for [-32768, 32767]

//load cell output depends on the supply, measurements have to be
//adjusted when supply varies
#define ZERO 10 //loadcell zero
#define Vs_CAL 5.115 //V, measured voltage supply when calibrated

//calibration parameters, measurement to force
#define SCALE 9.85205 //pendent calibratge
#define OFFSET -7.76663 //zero calibratge
// R^2 de 0.99995

float PRELOAD, Vref;

void ADC_SetVREF();

float get_thrust();

void set_preloading(int n);

float get_measurement();

#endif