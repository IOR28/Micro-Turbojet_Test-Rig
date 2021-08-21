#include "temperature.h"

adc_0_channel_t channel = 0x30;

float measure_Tt(int phase) {
    switch (phase){
        case 1: channel = 0x8; return compute_Thermocouple(); //pin PB5 -> AIN8
        case 33: channel = 0x9; return compute_RTD(); //pin PB4 -> AIN9
        case 3: channel = 0x3; return compute_Thermocouple(); //pin PA3 -> AIN3
        case 4: channel = 0x4; return compute_Thermocouple(); //pin PA4 -> AIN4
        case 9: channel = 0x5; return compute_Thermocouple(); //pin PA5 -> AIN5
        default: channel = 0x30; return 0; //ground, no reading T = 0
    }
}

float compute_Thermocouple() {
    //Single ended measurement without gain:
    adc_result_t res = ADC0_GetDiffConversion(false, channel, 0x30);
    float v = ADC_DifftoVoltage(false, res);
    
    //AD8495 formula
    float t_C = v/0.005;
    
    //delete fake measurements
    if (t_C < 0.5)
        t_C = 0;
    else if (t_C > 1200)
        t_C = 0;
    
    return t_C + 273.15;
}

float compute_RTD() {
    //Differential measurement with gain:
    diff_adc_result_t res = ADC0_GetDiffConversion(true, channel, REF_CHANNEL);
    float v = ADC_DifftoVoltage(true, res) * 1000; //in mV
    
    //find the resistance with signal conditioning values
    float r_pt = v + OFFSET;
    
    //PT100 formula
    float t_C = (r_pt - R_PT0)/ALPHA;
    
    //delete fake measurements
    if (t_C < -20)
        t_C = 0;
    else if (t_C > 600)
        t_C = 0;
    
    return t_C + 273.15;
}