/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	        Unittest.c

https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/
********************************************************************************/
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
#include "state_driven.h"
#include "TMP102.h"
#include <string.h>


uint8_t actual;
void unit_test(void){
	UCUNIT_Init();
	UCUNIT_TestcaseBegin("UNIT TESTING BEGINS");
	UCUNIT_CheckIsEqual(0x60,actual);
  	UCUNIT_CheckIsInRange(actual,0,80);
  	UCUNIT_CheckIs8Bit(actual);
  	UCUNIT_CheckIs16Bit(actual);
  	UCUNIT_CheckIs32Bit(actual);
  	UCUNIT_CheckIsBitSet(actual, 5);
  	UCUNIT_CheckIsBitClear(actual,5);
  	UCUNIT_WriteSummary();
 	UCUNIT_TestcaseEnd();
}

/** Reference************************************************************************************
 https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/
********************************************************************************************/
