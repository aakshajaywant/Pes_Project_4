/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	        LOGGER.C
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
#include "TMP102.h"
#include "fsl_device_registers.h"

extern uint8_t var_flag;
 //char str[40];
uint32_t *data_ptr;
extern char ch_arr[40][40];

//enum functions{
//	temp_reading=0,
//	temp_alert,
//	temp_average,
//	temp_disconnected
//}f;



int log_level(m,f)
{
if(m==0 && f==0)
{
	PRINTF("\n \r ****************************************************");
	PRINTF("\n \r TEST MODE:TEMP_READING FUNCTION ,%s",ch_arr[0]);
	PRINTF("\n \r****************************************************");
}
else if(m==0 && f==1)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r TEST MODE :Temp_Average, %s",ch_arr[1]);
	PRINTF("\n \r****************************************************");
}
else if(m==0 && f==2)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r TEST MODE :Temp_Alert ,%s",ch_arr[2]);
	PRINTF("\n \r****************************************************");
}
else if(m==0 && f==3)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \rTEST MODE :Temp_Disconnected ,%s",ch_arr[3]);
	PRINTF("\n \r****************************************************");
}
else if(m==0 && f==3)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r TEST MODE:Temp_Disconnected ,%s",ch_arr[4]);
	PRINTF("\n \r****************************************************");
}
else if(m==0 && f==4)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r TEST MODE:LED_ON  %s ",ch_arr[5]);
	PRINTF("\n \r****************************************************");
}
else if(m==0 && f==5)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r TEST MODE: %s",ch_arr[6]);
	PRINTF("\n \r****************************************************");
}
else if(m==1 && f==0)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r DEBUG MODE:Temp_Reading ,%s",ch_arr[0]);
	PRINTF("\n \r****************************************************");
}
else if(m==1 && f==1)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r DEBUG MODE:Temp_Average %s",ch_arr[1]);
	PRINTF("\n \r****************************************************");
}
else if(m==1 && f==2)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r DEBUG MODE :Temp_Alert %s",ch_arr[2]);
	PRINTF("\n \r****************************************************");
}
else if(m==1 && f==3)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r DEBUG MODE:Temp_Disconnected %s",ch_arr[3]);
	PRINTF("\n \r****************************************************");
}
else if(m==1 && f==4)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r DEBUG MODE:LED_ON %s",ch_arr[4]);
	PRINTF("\n \r****************************************************");
}
else if(m==0 && f==5)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r DEBUG MODE:SWITCH STATE MACHINES %s",ch_arr[5]);
	PRINTF("\n \r****************************************************");
}
else if(m==2 && f==0)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r STATUS MODE:Temp Reading %s",ch_arr[0]);
	PRINTF("\n \r****************************************************");
}
else if(m==2 && f==1)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r STATUS MODE:Temp_average %s",ch_arr[1]);
	PRINTF("\n \r****************************************************");
}
else if(m==2 && f==2)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r STATUS MODE:Temp_Alert %s",ch_arr[2]);
	PRINTF("\n \r****************************************************");
}
else if(m==2 && f==3)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r STATUS MODE:Temp_Disconnected %s",ch_arr[3]);
	PRINTF("\n \r****************************************************");
}
else if(m==2 && f==4)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r STATUS MODE:LED_ON %s",ch_arr[4]);
	PRINTF("\n \r****************************************************");
}
else if(m==0 && f==5)
{
	PRINTF("\n \r****************************************************");
	PRINTF("\n \r STATUS MODE:SWITCH STATE MACHINES %s",ch_arr[5]);
	PRINTF("\n \r****************************************************");
}
}

int log_integer(size_t x)
{
	PRINTF(" %d ",x);
	return 0;
}


void log_string(char *ptr_st)
{
	PRINTF("\n \r %s",ptr_st);
}


