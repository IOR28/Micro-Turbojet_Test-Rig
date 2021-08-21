#include "ADC_toVoltage_Pressure.h"

float ADC_toVoltage(adc_result_t res) 
{
        return res * V_REF/half_M; //bits set to 16!!
}
