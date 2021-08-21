#include "i2c_ThrustFlow.h"

uint8_t reg;
int y = 0;
uint8_t* temp;

void read_reg() {
    reg = I2C0_Read();
}

void write_float() {
    switch (reg){
        case 0x54: temp = (uint8_t*)&Thrust; break;
        case 0x46: temp = (uint8_t*)&Flow; break;
        default: break;
    }
}

void send_data() {
    if (reg==0) {
        I2C0_Write(0x0A);
        return;
    }
    if (!y)
        write_float();

    I2C0_Write(temp[y]);
    y++;
}

void clear() {
    y = 0;
    reg = 0;
}