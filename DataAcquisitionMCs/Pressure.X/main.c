#include "mcc_generated_files/mcc.h"
#include "transducer.h"

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    /* Replace with your application code */
    
    Pt3 = 101325.0;
    Pt4 = 101325.0;
    Pt9 = 101325.0;
    P9 = 101325.0;
    
    _delay_ms(500);
    
    while (1){
        
        Pt3 = measure_Pt(3);
        Pt4 = measure_Pt(4);
        Pt9 = measure_Pt(9);
        P9 = measure_Pt(10);
        
        _delay_ms(350);
    }
}
/**
    End of File
*/