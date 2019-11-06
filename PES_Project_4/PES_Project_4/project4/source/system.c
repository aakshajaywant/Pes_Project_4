/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	        system.c
********************************************************************************/
/********************* References ********************************************************
 https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/
************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "system.h"
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
#include "UCunit.h"
#include <string.h>
#include "logger.h"

/* Stub: Initialize your hardware here */
void System_Init(void)
{

	log_string("\n \r Initialization of system done");
}

/* Stub: Shutdown your hardware here */
void System_Shutdown(void)
{
	PRINTF("\n \r Shutdowns the system");
	exit(0);
}

/* Stub: Recover your system from a safe state. */
void System_Recover(void)
{
	/* Stub: Recover the hardware */
	/* asm("\tRESET"); */
	PRINTF("\n \r System recovers.\n");
	exit(0);
}

/* Stub: Put system in a safe state */
void System_Safestate(void)
{
	PRINTF("\n \r Safe state of system\n");
	exit(0);
}

/* Stub: Write a string to the host/debugger/simulator */
void System_WriteString(char * string)
{
	PRINTF(string);
}

void System_WriteInt(int d)
{
	PRINTF(" %i", d);
}
