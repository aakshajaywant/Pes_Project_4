/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	    state_driven.c
********************************************************************************/
/**************Header files**************/

#include <stdint.h>
#include <stdlib.h>
#include "state_driven.h"
#include "TMP102.h"
#include <stdio.h>
#include "tabledriven.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "led.h"
#include "logger.h"
#include "fsl_device_registers.h"

/*****global Declaration******/
uint8_t element=0;
uint8_t timeout_var=0;
uint8_t disp_ele=0;
uint8_t arr[100];
uint8_t var_print=1;
uint8_t average_read=0,total_read=0;
uint8_t neg_temp;
uint8_t timeout_table;
extern uint8_t post;
extern uint8_t disc_value;
extern uint8_t disc_buffer;
uint8_t time_var=0;


typedef enum
	{
		temp_reading , temp_average, temp_alert, temp_disconnected,LED_on
	}tstate;


	tstate r = temp_reading;

	enum modes{
		test=0,
		debug,
		status
	}m;

/***Delay for 15sec***/
	void delay(uint32_t d)
	{
		uint32_t count = d*3450;	/***7000****** As clock is 8MHz *****/
		while(count!=0)
		{
	count--;
		}
	}

enum modes m=0;
/******Power on Self Test**************/
int post_condition(void)
{

	uint8_t post_buffer;
	post_buffer = read_byte(0x90,0x01);
	extern uint8_t actual;
	actual=post_buffer;
	return post_buffer;

}
/************Disconnect Condition*********/
//int disc_condition(void)
//{
//	disc_buffer = read_byte(0x90,0x01);
//	return disc_buffer;
//}


/*****Temperature read function*********/
uint8_t handle_timeout(void)
{

	log_level(m,0);		//Log_level
	init_LED();			//Initialize LED
	led_wait();
	log_level(m,4);
	disc_value=read_byte(0x90,0x01);
	log_string("checks the disconnect condition");
	if (disc_value != 0x60 || disc_value != 0x62)	/****disconnect condition***/
			{
			return temp_disconnected;
			}
	else
	{
		if(timeout_var<4)
		{
			arr[element] = read_byte(0x90,0x00); 	//taking 1st temp reading

			log_string("the temp value is:");
			log_integer(arr[element]);

			if(m==1||m==2){
				log_string("\t \t \t \t Timeout ");
				log_integer(var_print);
			}
		var_print++;
		timeout_var++;
		//disc_value=disc_condition();
		/**for temperature greater than 0***/
		if(arr[element]>0)
		{
			return temp_average;
		}
		else if(arr[element]<=0)	/**for temperature less than 0***/
		{
		return temp_alert;
		}

		}
	}
}
/***********Temperature Average***/
uint8_t handle_complete(void)
{
	log_level(m,1);
	init_LED();
	led_wait();
	log_level(m,4);

disc_value=read_byte(0x90,0x01);
log_string("checks the disconnect condition");
if (disc_value != 0x60 || disc_value != 0x62)	/****disconnect condition***/
{
	return temp_disconnected;
}
else
{

	if(arr[element]>0)
	{
		//disc_value = disc_condition();
		if(timeout_var == 4)
		    	{
					timeout_var=0;
		    		Table_Driven();
		    	}
		else{
    if(m==1||m==2)
    {
    log_string("The last temperature reading  ");
    log_integer(disp_ele);
    log_string(" is: ");
    log_integer(arr[disp_ele]);
    }
    total_read=0;
    for(uint8_t i=0;i<timeout_var;i++)					// for average
    {
    	total_read = total_read + arr[i];
    }
    average_read= total_read/(timeout_var);
    if(m==1||m==2)
    {
        log_string("The current average temperature reading is:");
        log_integer(average_read);
        log_string("\n");
       }
    element++;
    	delay(10000);
    disp_ele++;

    return temp_reading;
		}
	}

	else if (arr[element]<=0)
	{
		//disc_value = disc_condition();
		log_level(m,1);
		init_LED();
		led_wait();
		log_level(m,4);
		if(m==1||m==2)
		{
		log_string("The last temperature reading is:\t ");
		log_integer(disp_ele);
		log_integer(arr[disp_ele]);
		}
		timeout_var++;
		total_read=0;
		for(uint8_t i=0;i<timeout_var;i++)
		{
		  total_read = total_read + arr[i];
		}
		//  total_read = total_read + (neg_temp);
		  average_read= total_read/(timeout_var);
		  if(m==1||m==2)
		 {
          log_string("The current average temperature reading is:\t");
          log_integer(average_read);
		 }
		  element++;
		  delay(10000);
		  disp_ele++;
		  if(timeout_var == 4)
		  {
			  timeout_var=0;
		  }
		  return temp_disconnected;
	}
}
}
/**********Temperature alert condition*******/
uint8_t handle_alert(void)
{
	//disc_value = disc_condition();
	log_level(m,2);
	init_LED();
	led_alert();
	log_level(m,4);
	disc_value=read_byte(0x90,0x01);
	log_string("checks the disconnect condition");
	if(disc_value != 0x60 || disc_value != 0x62)
	{
		return temp_disconnected;
	}
	else
	{
	log_level(m,2);
	init_LED();
	led_alert();
	log_level(m,4);
	neg_temp = arr[element];
	log_integer(arr[element]);
	log_string(" is the negative temperature received");

	return temp_average;
	}
}

uint8_t handle_disconnect(void)
{
	log_level(m,3);
	init_LED();
	led_error();
	log_level(m,4);
	disc_value = read_byte(0x90,0x00);
	log_string("Connection has been disconnected");
	exit(0);
}

void State_Driven(void)
{
	tstate r = temp_reading;
	timeout_var = 0;
	element = 0;
	disp_ele = 0;
	average_read = 0;
	var_print = 1;
	log_string("*************STATE DRIVEN STATE MACHINE BEGINS***********");

while(1)
  {
    	switch(r)
    	{

    	case temp_reading:
					   	   r =  handle_timeout();
					   	   break;
    	case temp_average:
    						r = handle_complete();
    						break;

    	case temp_alert:
    						r = handle_alert();
    						break;

    	default:
							r = handle_disconnect();
							break;

    	}
}

}


