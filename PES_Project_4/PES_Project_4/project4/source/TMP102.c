/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	    TMP102.c
********************************************************************************/
/**************Header files**************/

#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <led.h>
#include "TMP102.h"
#include "fsl_device_registers.h"

void I2C_Master_Init(void)
{
	/* Enable clock for I2C0 module */
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

	/* Enable clock for Port C */
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;


	/* Port C MUX configuration */
	PORTC->PCR[8] |=  PORT_PCR_MUX(2);
	PORTC->PCR[9] |=  PORT_PCR_MUX(2);


	/* Configure Divider Register */
	I2C0->F |= I2C_F_ICR(0x11) | I2C_F_MULT(0);

	/* Enable I2C module and interrupt */
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	/*select high drive mode*/
	I2C0->C2 |= (I2C_C2_HDRS_MASK);

	/* Enable TX mode */
	//I2C0_C1 |= I2C_C1_TX_MASK;

	/* Enable I2C0 NVIC interrupt */
	//Enable_irq(INT_I2C0 - 16);
}




void write_byte(uint8_t dev,uint8_t reg,uint8_t data)
{
	I2C_TRAN;
	I2C_M_START;
	I2C0->D = dev;
	I2C_WAIT;

	I2C0->D = reg;
	I2C_WAIT;

	I2C0->D = data;
	I2C_WAIT;
	I2C_M_STOP;
}


uint8_t read_byte(uint8_t dev,uint8_t reg)
{
	uint8_t data=0;
	//uint8_t i;
	I2C_TRAN;     		// set to transmit mode in Control 1 register
	I2C_M_START;  		// master mode select

//	for(i=0;i<3;i++)
//	{
//	I2C0->D = buffer[i] ;
//	I2C_WAIT;
//	}
	I2C0->D = dev;
	I2C_WAIT;

	I2C0->D = reg ;		//
	I2C_WAIT;

//	I2C0->D = buffer[i];
//	I2C_WAIT;

	I2C_M_RSTART;
	I2C0->D = (dev | 0x1);
	I2C_WAIT;

	I2C_REC;
	NACK;

	data = I2C0->D;
	I2C_WAIT;

	I2C_M_STOP;
	data = I2C0->D;

	return data;
}


/**********************************References*****************************************
 1.ARM CORTEX M BASED MICROCONTROLLERS,DEAN 2017,ARM EDUCATION MEDIA
 ***********************************************************************************/
