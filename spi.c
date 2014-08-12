#include "config.h"
#include <msp430x14x.h>
#include "spi.h"

void initPortSPI()
{
    P6SEL = 0x00;
    P6DIR = 0xFF;
}


void readByteFormSPI(u8 address, u8 *data)
{
    u8 i;

    P6OUT &= (~0x80);
    address |= 0x80;
    P6OUT |= 0x10;

    for (i = 0; i < 8; ++i) {
        if (0x80 == (address & 0x80)) {
            P6OUT |= 0x10;
        } else {
            P6OUT &= (~0x10);
        }
        P6OUT &= (~0x40);
        delay_us(50);
        P6OUT |= 0x40;
        address <<= 1;
    }
    P6OUT |= 0x40;
    delay_us(50);
    P6OUT &= (~0x40);
    for (i = 0; i < 8; ++i) {
        P6OUT |= 0x40;
        delay_us(50);
        if ((P6IN  & (~0x20)) != 0) {
            *data |= 0x01;
        } 
        P6OUT &= (~0x40);
        *data <<= 1;
    }
    P6OUT |= 0x80;
}

void readBytesFormSPI(u8 *data, u8 address, u8 n)
{
    u8 i;
    for (i = 0; i < address; ++i) {
        readByteFormSPI(address, (data + i));
    }
}

void writeByteFormSPI(u8 address, u8 data)
{
    P6OUT &= (~0x80);
    u8 i;
    address &= ~0x80;
    P6OUT |= 0x10;
    for (i = 0; i < 8; ++i) {
        if (0x80 == (address & 0x80)) {
            P6OUT |= 0x10;
        } else {
            P6OUT &= (~0x10);
        }
        P6OUT &= (~0x40);
        delay_us(50);
        P6OUT |= 0x40;
        address <<= 1;
    }

    for (i = 0; i < 8; ++i) {
        if (0x80 == data & 0x80) {
            P6OUT |= 0x10;
        } else {
            P6OUT &= (~0x10);
        }
        P6OUT &= (~0x40);
        delay_us(50);
        P6OUT |= 0x40;
        data <<= 1;
    }
    P6OUT |= 0x80;
}