#include <MSP430x14x.h>
#include "config.h"
#include "LDC1000_cmd.h"
#include "spi.h"

#define RPMIN 0x3A
#define RPMAX 0x13

u16 proximtyData;
u32 frequencyData;
int i;

u8 getProximtyData(u16 *proximtyData)
{
    u8 data;
    readByteFormSPI(LDC1000_CMD_STATUS, &data);
    if (data & 0x40 == 0x40) {
        return 0;
    }
    readByteFormSPI(LDC1000_CMD_PROXLSB, &data);
    *proximtyData += data;
    readByteFormSPI(LDC1000_CMD_PROXMSB, &data);
    *proximtyData <<= 8;
    *proximtyData += data;
    return 1;
}

u8 getFrequencyData(u32 *frequencyData)
{
    u8 data;
    readByteFormSPI(LDC1000_CMD_STATUS, &data);
    if (data & 0x40 == 0x40) {
        return 0;
    }
    readByteFormSPI(LDC1000_CMD_FREQCTRLSB, &data);
    *frequencyData += data;
    readByteFormSPI(LDC1000_CMD_FREQCTRMID, &data);
    *frequencyData <<= 8;
    *frequencyData += data;
    readByteFormSPI(LDC1000_CMD_FREQCTRMID, &data);
    *frequencyData <<= 8;
    *frequencyData += data;
    return 1;
}


void main(void) {

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    /*****************TEST*********TEST***************TEST*********/
    Clock_Init();
    initPortSPI();
    
    //write to register
    writeByteFormSPI(LDC1000_CMD_RPMAX,       RPMAX);
    writeByteFormSPI(LDC1000_CMD_RPMIN,       RPMIN);
	writeByteFormSPI(LDC1000_CMD_SENSORFREQ,  0x94);
	writeByteFormSPI(LDC1000_CMD_LDCCONFIG,   0x17);
	writeByteFormSPI(LDC1000_CMD_CLKCONFIG,   0x02);
	writeByteFormSPI(LDC1000_CMD_INTCONFIG,   0x02);

	writeByteFormSPI(LDC1000_CMD_THRESHILSB,  0x50);
	writeByteFormSPI(LDC1000_CMD_THRESHIMSB,  0x14);
	writeByteFormSPI(LDC1000_CMD_THRESLOLSB,  0xC0);
	writeByteFormSPI(LDC1000_CMD_THRESLOMSB,  0x12);

	writeByteFormSPI(LDC1000_CMD_PWRCONFIG,   0x01);

    while (1)
    {
        getProximtyData(&proximtyData);
        getFrequencyData(&frequencyData);
        i++;
    }
}