/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	    led.c
********************************************************************************/

#include "led.h"
#include <stdint.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"

void init_LED(void);
void led_alert(void);
void led_error(void);
void led_wait(void);

void init_LED(void)
{
      BOARD_InitBootPins();
      BOARD_InitBootClocks();
      BOARD_InitBootPeripherals();
      BOARD_InitDebugConsole();
      LED_BLUE_INIT(1);
      LED_RED_INIT(1);
      LED_GREEN_INIT(1);
}

void led_alert(void)		//temp alert state
{
	LED_RED_OFF();
	LED_GREEN_OFF();
	LED_BLUE_ON();
	//delay(10000);
}

void led_error(void)	//error or disconnected state
{
	LED_GREEN_OFF();
	LED_BLUE_OFF();
	LED_RED_ON();
	//delay(10000);
}

void led_wait(void)	//temp reading state
{
	LED_RED_OFF();
	LED_BLUE_OFF();
	LED_GREEN_ON();
	//delay(10000);
}


//void delay(uint32_t d)
//{
//	uint32_t count = d*7000;	/****** As clock is 8MHz *****/
//	while(count!=0)
//	{
//		count--;
//	}
//}



