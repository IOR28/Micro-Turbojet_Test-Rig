#ifndef flowmeter_h
#define flowmeter_h

//start timer and enable PB4 interrupts
void flowmeter_init();

//Performs a 200ms measurement, if frequency is lower than 10Hz indicates 0
void measure_flow();

//start or stop counting when PB4 detects raising edge
void set_flag();

//compute fuel consumption and flow once the counter has finished
// total_fuel in liters
// flow in liters per minute
void count();

//gets
float get_flow();
float get_freq();
int get_count();

#endif