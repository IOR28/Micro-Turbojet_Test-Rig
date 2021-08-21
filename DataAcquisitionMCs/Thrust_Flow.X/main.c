#include "mcc_generated_files/mcc.h"
#include "flowmeter.h"

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    flowmeter_init();   
    
    Thrust = 0.0;
    Flow = 0.0;
    _delay_ms(500);
    
    ADC_SetVREF();
    set_preloading(10); //measure preload with 10 averages
    
    /* Replace with your application code */
    while (1){
        measure_flow();
        Flow = get_flow();

        Thrust = get_thrust();
        
        ADC_SetVREF(); //monitor supply voltage
        
        _delay_ms(200);
    }
}
/**
    End of File
*/