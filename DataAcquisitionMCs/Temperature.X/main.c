#include "mcc_generated_files/mcc.h"
#include <util/delay.h>
#include "ADC_toVoltage_Temperature.h"
#include "temperature.h"

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    
    Tt1 = 268.15;
    Tt3 = 268.15;
    Tt4 = 268.15;
    Tt5 = 268.15;
    
    _delay_ms(500);
    ADC_SetVREF(); //Compute Vref
    
    while (1){

        //thermocouples
        Tt1 = measure_Tt(1);
        Tt4 = measure_Tt(4);
        Tt5 = measure_Tt(9);
        
        //thermocouple or RTD
        bool RTD = false;
        if (RTD)
            Tt3 = measure_Tt(33);
        else
            Tt3 = measure_Tt(3);
        
        ADC_SetVREF(); //monitor supply voltage

        _delay_ms(750);
    }
}
/**
    End of File
*/