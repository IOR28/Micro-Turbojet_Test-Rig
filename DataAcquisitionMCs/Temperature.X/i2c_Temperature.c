#include "i2c_Temperature.h"

uint8_t reg;
int y = 0;
uint8_t* temp;

void read_reg() {
    reg = I2C0_Read();
}

void write_float() {
    switch (reg){
        case 0x55: temp = (uint8_t*)&Tt1; break;
        case 0x57: temp = (uint8_t*)&Tt3; break;
        case 0x58: temp = (uint8_t*)&Tt4; break;
        case 0x59: temp = (uint8_t*)&Tt5; break;
        default: break;
    }
}

void send_data() {
    if (reg==0) {
        I2C0_Write(0x0C);
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


