#include "i2c_Pressure.h"

uint8_t reg;
int y = 0;
uint8_t* temp;

void read_reg() {
    reg = I2C0_Read();
}

void write_float() {
    switch (reg){
        case 0x63: temp = (uint8_t*)&Pt3; break;
        case 0x64: temp = (uint8_t*)&Pt4; break;
        case 0x69: temp = (uint8_t*)&Pt9; break;
        case 0x60: temp = (uint8_t*)&P9; break;
        default: break;
    }
}

void send_data() {
    if (reg==0) {
        I2C0_Write(0x0B);
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

