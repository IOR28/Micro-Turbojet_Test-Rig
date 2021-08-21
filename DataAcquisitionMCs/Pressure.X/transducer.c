#include "transducer.h"

adc_0_channel_t channel = 0x30;
float FS = 0;

float measure_Pt(int phase) {
    switch (phase){
        case 3: channel = 0x8; FS = 4.0; break; //pin PB5 -> AIN8
        case 4: channel = 0x3; FS = 4.0; break; //pin PA3 -> AIN3
        case 9: channel = 0x5; FS = 2.5; break; //pin PA5 -> AIN5
        case 10: channel = 0x7; FS = 2.5; break; //pin PA7 -> AIN7
        default: channel = 0x30; FS = 0; //ground, no reading P = 0
    }
    
    return compute_P();
}

float compute_P() {
    //Single ended measurement without gain
    adc_result_t res = ADC0_GetDiffConversion(channel, 0x30);
    float voltage = ADC_toVoltage(res);
    
    //Find the pressure using the 4-20mA scale
    float v_mv = voltage*1000;
    float p_bar = (v_mv/120 - 4) * FS/16;
    
    //delete fake measurements
    if (p_bar < 0)
        p_bar = 1.01325;
    else if (p_bar > 1.1*FS) 
        p_bar = 1.01325;
    
    return p_bar * 100000;
}

