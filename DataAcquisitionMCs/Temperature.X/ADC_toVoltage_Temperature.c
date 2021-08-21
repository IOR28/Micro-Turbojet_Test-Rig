#include "ADC_toVoltage_Temperature.h"

float Vref;

void ADC_SetVREF()
{
    //Measure the 1.024V reference without gain
    adc_result_t ref = ADC0_GetDiffConversion(0, DAC, 0x30);

    //res = DAC*G/Vref * M, gain set to 1 and 16bits differential!!!
    Vref = DACREF/ref*half_M;
    return;
}

float ADC_GetVREF() {
    return Vref;
}

//Function for differential measurements with gain
float ADC_DifftoVoltage(bool viaPGA, diff_adc_result_t diffres)
{
    if (Vref == 0)
        return -1;
    else
        if (viaPGA)
            return diffres * Vref/(Gain*half_M); //gain and 16bits differential!!
        else
            return diffres * Vref/half_M;
}