/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	        MAIN.C
********************************************************************************/
/**************Header files**************/
#include <stdint.h>
#include <stdio.h>
#include "TMP102.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include <time.h>
#include "led.h"
#include "logger.h"
#include <state_driven.h>
#include "UCunit.h"
#include <string.h>
#include "unittest.h"

/***********global variables**********/
uint8_t post;
uint8_t disc_buffer;
uint8_t disc_value;

/**********alert pin function***********/
void set_ptrreg(void)
{
	write_byte(0x90,0x01,0x62);
	write_byte(0x90,0x01,0xA0);
	write_byte(0x90,0x02,0x28);
	write_byte(0x90,0x02,0x00);

}
/****function and mode enumerations*******/
enum functions{
	temp_reading=0,
	temp_alert,
	temp_average,
	temp_disconnected
}f;

typedef enum {
	test=0,
	debug,
	status
}mode;


mode mo=0;

char ch_arr[40][40]={   "Temperature Reading mode",
						"Temperature average",
						"Temperature alert mode",
						"Temperature Disconnect",
						"LED is initialized",
						"Switches to Other State Machine"
					};


int main(void)
{

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    I2C_Master_Init();

    if(mo==0)
    {
    		log_string("******TEST MODE ON *******");
    		/***uCunit testing*******/
        	unit_test();
     }
    else if(mo==1)
    {
    	log_string("******DEBUG MODE ON **********");
    }
    else if(mo==2)
    {
    	log_string("******NORMAL/STATUS MODE ON *******");
    }

/*****check post*****/
    post = post_condition();

    if(post == 0x60 || post == 0x62)
    {
    	log_string("\n \r POST SUCCESSFUL");
    	//set_ptrreg();
    	State_Driven();			/****State driven state machine**/
    }

    else
    {
    	log_string("\n \r POST UNSUCCESSFUL");
    	handle_disconnect();
    }

    return 0 ;
}
