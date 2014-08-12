#ifndef _SPI_H_
#define _SPI_H_

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

void initPortSPI();
void readByteFormSPI(u8 address, u8 *data);
void writeByteFormSPI(u8 address, u8 data);

#endif