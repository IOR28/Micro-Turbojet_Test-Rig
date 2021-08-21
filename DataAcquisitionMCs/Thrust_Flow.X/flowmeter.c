#include "flowmeter.h"
#include "mcc_generated_files/mcc.h"

int flag, done;
uint16_t start, stop;
uint16_t pulses;
const long TCB0_freq = 156250;
float freq, flow;

void flowmeter_init() {
    PB4_SetDigitalInput();
    //PORTB_PB4_SetInterruptHandler(set_flag);
    done = 0;
    flag = 0;
    freq = 0;
    flow = 0;
}

void measure_flow() {
    //set initial parameters
    TCB0_WriteTimer(0x00);
    done = 0;
    flag = 0;
    
    //Enable interrupts and wait 200ms to measure
    PB4_EnableInterruptForRisingEdge();
    _delay_ms(100); //Minimum detectable frequency 20Hz!!
    PB4_DisableInterruptOnChange();
    
    //if not done that means there where no 2 consecutive rising edges
    //in the 200ms period: f=0Hz or <10Hz
    if (!done || freq < 10) {
        freq = 0;
        flow = 0;
    }
    
}

void set_flag() {
    if (!flag) {
        start = TCB0_ReadTimer();
        flag = 1;
    }
    else {
        stop = TCB0_ReadTimer();
        count();
        
        flag = 0;
    }
}


void count() {
    pulses = stop - start;
    freq = TCB0_freq/(float)pulses;
    
    flow = freq * (60.0f/22000); // 60/22000 = 1 lpm
    done = 1;
}

float get_flow() {
    return flow;
}

float get_freq() {
    return freq;
}

int get_count() {
    return pulses;
}