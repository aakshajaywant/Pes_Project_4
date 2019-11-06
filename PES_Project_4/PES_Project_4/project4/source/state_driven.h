/******************************************************************************
								PES PROJECT 4
   	   	   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
                   Cross Platform IDE: MCUXpresso IDE v11
                       Cross-Compiler: ARM GCC (FB version)
 	 	 	 	 	 	 	    state_driven.h
********************************************************************************/

#include <stdint.h>

#ifndef STATE_DRIVEN_H_
#define STATE_DRIVEN_H_

uint8_t handle_timeout(void);
uint8_t handle_complete(void);
uint8_t handle_alert(void);
uint8_t handle_disconnect(void);
void State_Driven(void);

int post_condition(void);

int disc_condition(void);



#endif
