/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	    master.h
********************************************************************************/

#ifndef TMP102_H_
#define TMP102_H_
#include "stdint.h"

#define SLAVE_ADDRESS 0x91

#define BUFFER_SIZE	10

#define WRITE	0x00
#define	READ	0x01

#define I2C_M_START     I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP      I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART    I2C0->C1 |= I2C_C1_RSTA_MASK
#define I2C_TRAN 		I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC 		I2C0->C1 &= ~I2C_C1_TX_MASK
#define I2C_WAIT 		while((I2C0->S & I2C_S_IICIF_MASK)==0) {} \
							I2C0->S |= I2C_S_IICIF_MASK;
#define NACK 			I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK 			I2C0->C1 &= ~I2C_C1_TXAK_MASK



void I2C_Master_Init(void);
void write_byte(uint8_t dev, uint8_t reg, uint8_t data);

uint8_t read_byte(uint8_t dev, uint8_t reg);

#endif

