/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	    tabledriven.c
********************************************************************************/
/**************Header files**************/

#include "tabledriven.h"
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

/**************Global declaration**************/
uint8_t telement=0;
uint8_t ttimeout_var=0;
uint8_t tdisp_ele=0;
uint8_t tarr[100];
uint8_t tvar_print=1;
uint8_t taverage_read=0,ttotal_read=0;
uint8_t tneg_temp;
uint8_t ttimeout_table;
uint8_t ttime_var=0;
//extern uint8_t arr[100];
extern uint8_t post;
extern uint8_t disc_value;

int Sm_tempread(void);
int Sm_tempavg(void);
int Sm_tempalert(void);

enum module{
	test=0,
	debug,
	status
}md;
enum module md=0;

/*******Disconnect*********/
int Sm_tempdisc(void)
{

	//log_string("Connection has been disconnected");
	log_level(md,3);
		init_LED();
		led_error();
		log_level(md,4);
	_exit(0);
	return 0;
}


typedef char tevent;

typedef enum state
{
	temp_reading , temp_average, temp_alert , temp_disconnected

}tstate;



typedef struct
{
	tstate state;
	tevent trigger_event[30];
	int (*func_ptr)(void);

}StateMachinetype;

StateMachinetype StateMachine[10] =
{
		{temp_reading, "completeevent",&Sm_tempavg},
		{temp_average, "timeoutevent", &Sm_tempread},
		{temp_reading, "alertevent", &Sm_tempalert},
		{temp_alert, "completeevent", &Sm_tempavg},
		{temp_alert, "disconnectevent", &Sm_tempdisc},
		{temp_reading, "disconnectevent", &Sm_tempdisc},
		{temp_average, "disconnectevent", &Sm_tempdisc},
		{temp_disconnected,"disconnectevent", &Sm_tempdisc}
};

StateMachinetype *s_p = &StateMachine[0];

void Table_Driven()
{
	telement=0;
	ttimeout_var=0;
	tdisp_ele=0;
	tvar_print=1;
	taverage_read=0;
	ttotal_read=0;
	ttime_var=0;
	log_string("/*************************TABLE driven state Machine Begins************************/");
	Sm_tempread();
}


/*****Temperature read function*********/
int Sm_tempread(void)
{

disc_value=read_byte(0x90,0x01);
log_string("checks the disconnect condition");
if (disc_value == 0x00)	/****disconnect condition***/
{
		Sm_tempdisc();
}
else
{
//uint8_t i=0;
	if(ttimeout_var<4)				/************* timeout 0,1,2,3********************************************/
	{
		log_level(md,0);
		init_LED();
		led_wait();
		log_level(md,4);
		//	disc_value = disc_condition();
			tarr[telement] = read_byte(0x90,0x00); 	// repeat taking 1st temp reading
		//	arr[telement]=arr[telement]+arr[telement]*0.0625;
			log_string("The temperature value is");
			log_integer(tarr[telement]);
			if(md==1||md==2){
			log_string("\t \t \t timeout");
			log_integer(tvar_print);		//variable to print 1st, 2nd, 3rd timeout
			}
			tvar_print++;
			ttimeout_var++;

			if(tarr[telement]>0) 		/******************if temp is greater than 0**************************/
			{
			tstate state = temp_reading;
			tevent trigger_event[30] = "completeevent";

			for(uint8_t j=0;j<8;j++)
			{
							if (StateMachine[j].state==state && trigger_event)
								{


									s_p = &StateMachine[j];
									(*(s_p->func_ptr))();
								}

						}
			}
			else if(tarr[telement]<=0)		/*************for alert event********************************/
			{
			tstate state = temp_reading;
			tevent trigger_event[30] = "alertevent";
				for(uint8_t i=0;i<8;i++)
					{
					if(StateMachine[i].state==state && trigger_event)
							{
							s_p = &StateMachine[i];
								(*(s_p->func_ptr))();
							}
					}
			}

		}
else							/**********if timeout var is equal to 4*******************/
{
				tstate state = temp_average;
				tevent trigger_event[30] = "completeevent";
				for(uint8_t i=0;i<8;i++)
					{
					if( StateMachine[i].state == state && trigger_event)
						{
						s_p = &StateMachine[i];
						(*(s_p->func_ptr))();
						}
					}
}
}
	return 0;
}

/*****Temperature average function*********/
int Sm_tempavg(void)
{
			log_level(md,1);
			init_LED();
			led_wait();
			log_level(md,4);
//disc_value = disc_condition();
disc_value=read_byte(0x90,0x01);
log_string("checks the disconnect condition");
if (disc_value == 0x00)	/****disconnect condition***/
{
	Sm_tempdisc();
}
else
{
	if(tarr[telement]>0)						/***************when temp is greater than zero*********************/
	{
			if(ttimeout_var == 4)					/******************checks if 4th timeout has occured**************/
			{
			log_string("last timeout var value");
			log_integer(ttimeout_var);
			post = post_condition();				/***********calling POST condition func***************/
			log_string("value is");
			log_integer(post);

				if(post == 0x60 || post == 0x62)
					{
					  log_string("\n \r POST SUCCESSFUL");
					  //set_ptrreg();
					 // Table_Driven();
					  State_Driven();
					  log_level(md,5);
					 }
				else
					{
					  log_string("\n \r POST UNSUCCESSFUL");
					  handle_disconnect();
					}

			}
			else						/********* if timeout is not equal to 4************/
			{
				log_string("the last temperture reading");
				log_integer(tdisp_ele);
				log_string("is:");
				log_integer(tarr[tdisp_ele]);

				ttotal_read=0;
				for(uint8_t i=0;i<ttimeout_var;i++)
				{
				ttotal_read = ttotal_read + tarr[i];
				//printf("\n \r %d is total read",ttotal_read);
				}
				taverage_read= ttotal_read/(ttimeout_var);
				log_string("the current average temperature reading is:");
				log_integer(taverage_read);
				telement++;
//				for(uint16_t j=0;j<6500;j++)		//delay loop
//				{
//					__asm volatile("\n \r nop");
//				}
//				Init_SysTick();
//						SysTick_Handler();
				delay(10000);
			tdisp_ele++;						//variable to display last temperature reading
			tstate state = temp_average;
			tevent trigger_event[30] = "timeoutevent";
			for(uint8_t c=0;c<8;c++)
			{
				if( StateMachine[c].state == state && trigger_event)
				{
					s_p = &StateMachine[c];
					(*(s_p->func_ptr))();
				}
			}
   // return temp_reading;
		}
	}
	else if (tarr[telement]<=0)				/**************condition for when temperature is less than zero*******************/
	{		if(md==1||md==2)
		{
		log_string("the last temperture reading");
		log_integer(tdisp_ele);
		log_string("is:");
		log_integer(tarr[tdisp_ele]);
		}
		ttimeout_var++;
		ttotal_read=0;
		for(uint8_t m=0;m<ttimeout_var;m++)
		{
		  ttotal_read = ttotal_read + tarr[m];
		}
		//  ttotal_read = ttotal_read + (tneg_temp);
		  taverage_read= ttotal_read/(ttimeout_var);
		  if(md==1||md==2){
		  log_string("the current average temperature reading is:");
		  log_integer(taverage_read);
		  }
		  telement++;
//		  for(uint16_t j=0;j<6500;j++)
//		  {
//
//		   __asm volatile("nop");
//		   }
//		  Init_SysTick();
//		  SysTick_Handler();
		  delay(10000);
		  tdisp_ele++;
		  //return temp_disconnected;
		  tstate state = temp_disconnected;
		  tevent trigger_event[30] = "disconnectevent";
		  for(uint8_t b=0;b<8;b++)
		  {
		  	if( StateMachine[b].state == state && trigger_event[30])
		  	{
		  	s_p = &StateMachine[b];
		  	(*(s_p->func_ptr))();
		  	}
		  }
	}

}
	return 0;
}

/*****Temperature alert function*********/
int Sm_tempalert(void)
{	log_level(md,2);
	init_LED();
	led_wait();
	log_level(md,4);

disc_value=read_byte(0x90,0x01);
log_string("checks the disconnect condition");
if (disc_value == 0x00)	/****disconnect condition***/
{
	Sm_tempdisc();
}
else
{
	tneg_temp = tarr[telement];
	if(md==1||md==2){
	log_string("Negative temperature value is");
	log_integer(tarr[telement]);
	}
}
	return 0;
}

/**********************************References*****************************************
 1.https://kjarvel.wordpress.com/2011/10/26/table-driven-state-machine-using-function-pointers-in-c/
 ***********************************************************************************/

