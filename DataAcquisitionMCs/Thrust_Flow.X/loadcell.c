#include "mcc_generated_files/mcc.h"

void ADC_SetVREF()
{
    //Set reference as Vs, the same as the loadcell
    ADC0.CTRLC = 0x50;
    //Measure the 1.024V reference without gain
    adc_result_t ref = ADC0_GetDiffConversion(0, DAC, 0x30);
    
    //Return reference to 1024MV
    ADC0.CTRLC = 0x54;
    
    //res = DAC*G/Vref * M/2, gain set to 1 and 16bits!!!
    Vref = DACREF/ref*half_M;
    return;
}

float get_thrust() {
    
    float measurement = get_measurement();
    
    float T = 9.81*(SCALE*measurement + OFFSET)/1000 - PRELOAD;
    
    if (T <= 1) //Delete noise below 100g
        T = 0.0f;
    
    return T;
}

void set_preloading(int n) {
    float preloads = 0.0f;
    
    for (int i = 0; i < n; i++) {
        float measurement = get_measurement();
        
        float y = 9.81*(SCALE*measurement - OFFSET)/1000;
        
        if (y <= 1)
            y = 0.0f;
        
        preloads += y;
    }
    
    PRELOAD = preloads / n;
}

float get_measurement() {
    diff_adc_result_t x = ADC0_GetDiffConversion(true, 0x04, 0x06);
    
    //if Vref>Vs_CAL: output will be bigger than calibration, factor <1
    //if Vref<Vs_CAL: output will be smaller than calibration, factor >1
    float measurement = x * Vs_CAL/Vref - ZERO;
    
    return measurement;
}