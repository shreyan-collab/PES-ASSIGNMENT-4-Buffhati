/**
 * @file    statemachine.c
 * @brief   This source file consists of function definition which executes the
 * 			 traffic light sequence with cross-walk functionality
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU Expresso IDE, KL25Z Freedom development board
 * @References
 * 1) Howdy's Presentation 10,13,14 - To set GPIO port as an input, statemachine, interrupts
 * https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 * 2) Embedded Systems fundamentals with ARM Cortex-M based microcontroller by Alexander Dean
 */

#include <stdbool.h>
#include "statemachine.h"
#include "timer.h"
#include "touchslider.h"
#include "switch.h"
#include "pwm.h"
#include "log.h"


#define STOP_RED_VALUE 	 			(0x61)
#define STOP_GREEN_VALUE			(0x1E)
#define STOP_BLUE_VALUE 			(0x3C)

#define GO_RED_VALUE 	 			(0x22)
#define GO_GREEN_VALUE	 			(0x96)
#define GO_BLUE_VALUE   			(0x22)


#define CROSSWALK_RED_VALUE 	 	(0x00)
#define CROSSWALK_GREEN_VALUE	 	(0x10)
#define CROSSWALK_BLUE_VALUE   		(0x30)

#define WARNING_RED_VALUE			(0xFF)
#define WARNING_GREEN_VALUE 		(0xB2)
#define WARNING_BLUE_VALUE			(0x00)

#define START							(0)
#define STOP							(1)
#define TRANSITION_TO_GO				(2)
#define GO				 				(3)
#define TRANSITION_TO_WARNING			(4)
#define WARNING							(5)
#define TRANSITION_TO_STOP				(6)
#define CROSSWALK 						(7)
#define TRANSITION_TO_CROSSWALK			(8)
#define TRANSITION_FROM_CROSSWALK		(9)
#define CROSSWALK_LED_ON				(10)
#define CROSSWALK_LED_OFF				(11)

#ifdef DEBUG
#define STOP_GO_TIME					(80)
#define WARNING_TIME					(48)
#else
#define STOP_GO_TIME					(320)
#define WARNING_TIME					(80)
#endif

#define TRANSITION_TIME 				(16)
#define CROSSWALK_TIME 				   (160)

#define RESET 							(0)
#define SET								(1)

#define PRESSED							(1)
#define NOT_PRESSSED					(0)


extern bool flag;
extern volatile uint16_t checkTimeout;
uint8_t currentState=STOP;
int16_t redValue = 0;
int16_t greenValue = 0;
int16_t blueValue = 0;
int16_t redPreviousValue = 0;
int16_t greenPreviousValue = 0;
int16_t bluePreviousValue = 0;
int16_t percentageIncrement=0;

uint32_t touchValue=0;
uint8_t startTime=0;
bool button_state = false;
char state[9][26]={"START","STOP","TRANSITION_TO_GO","GO","TRANSITION_TO_WARNING","TRANSITION_TO_STOP",
			  "CROSSWALK","TRANSITION_TO_CROSSWALK","TRANSITION_FROM_CROSSWALK"};


/*
 * @brief Executes the traffic light sequence with cross-walk functionality
 *
 * The traffic light sequence consists of 9 states including STOP, GO, WARNING states
 * with cross-walk state triggered through touch silder or gpio push button
 *
 * @return void
 */
void statemachine()
{
  reset_timer();
  while(1)
  {
	if(flag == 1)
	{
	   button_state=check_button_pressed();
	   touchValue=Touch_Scan_LH();
	   if(currentState!=CROSSWALK && currentState!=TRANSITION_TO_CROSSWALK &&
		 (touchValue > 100 || button_state == PRESSED))
	   {
		   LOG("\nButton press is detected at %ld",now());
		   redPreviousValue=redValue;
		   greenPreviousValue=greenValue;
		   bluePreviousValue=blueValue;
		   percentageIncrement=0;
		   currentState=TRANSITION_TO_CROSSWALK;
		   reset_timer();
		   LOG("\nChanging from %s to TRANSITION_TO_CROSSWALK state at %ld",state[currentState],now());
	   }
	 flag=0;
	}

   	switch(currentState)
   	{
   		case STOP:

   			if(get_timer() < STOP_GO_TIME)
   			{
   				transition_state(START);
   			}
   			else if(get_timer() >= STOP_GO_TIME)
   			{
   				reset_timer();
   				percentageIncrement=0;
   				currentState=TRANSITION_TO_GO;
   				LOG("\nChanging from STOP to TRANSITION_TO_GO state at %ld",now());
   			}
   		break;

   		case TRANSITION_TO_GO:

   			if((checkTimeout == 1) && (get_timer() < TRANSITION_TIME))
   			{

   				checkTimeout =0;
   				transition_state(STOP);

   			}
   			else if(get_timer() >= TRANSITION_TIME)
   			{
   				reset_timer();
   				currentState=GO;
   				LOG("\nChanging from TRANSITION_TO_GO to GO state at %ld",now());

   			}
   		break;

   		case GO:
   			if(get_timer() >= STOP_GO_TIME)
   			{
   			    percentageIncrement=0;
   			    currentState=TRANSITION_TO_WARNING;
   			    reset_timer();
				LOG("\nChanging from GO to TRANSIITON_TO_WARNING state at %ld",now());

   			}
   		break;

   		case TRANSITION_TO_WARNING:
   			 if( (checkTimeout == 1) && get_timer() < TRANSITION_TIME)
   			 {
   				 checkTimeout =0;
   			     transition_state(GO);

   			 }
   			 else if(get_timer() >= TRANSITION_TIME)
   			 {
   			     reset_timer();
   			     currentState=WARNING;
   			     LOG("\nChanging from TRANSITION_TO_WARNING to WARNING state at %ld",now());
   			 }
   		break;

   		case WARNING:
   			if(get_timer() >= WARNING_TIME)
   		    {
   				percentageIncrement=0;
   		    	reset_timer();
   		    	currentState=TRANSITION_TO_STOP;
   		    	LOG("\nChanging from WARNING to TRANSITION_TO_STOP state at %ld",now());
   		    }
   		break;

   		case TRANSITION_TO_STOP:
   			if((checkTimeout == 1) && get_timer() < TRANSITION_TIME)
   			{
   			    checkTimeout=0;
   			    transition_state(WARNING);

   			}
   			else if(get_timer() >= TRANSITION_TIME)
   			{
   			    reset_timer();
   			    currentState=STOP;
   				LOG("\nChanging from TRANSITION_TO_STOP to STOP state at %ld",now());
   			}
   		break;

   		case TRANSITION_TO_CROSSWALK:
   			if((checkTimeout == 1) && get_timer() < TRANSITION_TIME)
   			{
   			    checkTimeout=0;
   			    transition_state(TRANSITION_TO_CROSSWALK);

   			}
   			else if(get_timer() >= TRANSITION_TIME)
   	    	{
   	    		reset_timer();
   	    		currentState=CROSSWALK;
   	    		LOG("\nchanging from TRANSITION_TO_CROSSWALK to CROSSWALK state %ld",now());
   	    	}
   			break;

   		case CROSSWALK:
   			if(get_timer() < CROSSWALK_TIME)
   			{

   				if((get_timer() % 16) <= 12)
   				{
   					transition_state(CROSSWALK_LED_ON);
   				}
   				else if(get_timer() % 16 > 12)
   				{
   					transition_state(CROSSWALK_LED_OFF);
   				}

   			}
   			if(get_timer()>= CROSSWALK_TIME)
   			{
   				reset_timer();
   				percentageIncrement=0;
   				currentState=TRANSITION_FROM_CROSSWALK;
   				LOG("\nchanging from CROSSWALK to TRANSITION_FROM_CROSSWALK state %ld",now());
   			}
   		break;

   		case TRANSITION_FROM_CROSSWALK:
   			{
   				 if( (checkTimeout == 1) && get_timer() < TRANSITION_TIME)
   				 {
   				    checkTimeout =0;
   				    transition_state(CROSSWALK);
   				 }
   				 else if(get_timer() >= TRANSITION_TIME)
   				 {
   				    reset_timer();
   				    currentState=GO;
   				    LOG("\nchanging from TRANSITION_FROM_CROSSWALK to GO state %ld",now());
   				 }
   			}
   		break;
   	}
  }
}

/*
 * @brief The red, green and blue values to be loaded with TPM modules is calculated
 * 		  depending on the states
 *
 * @param previous State to calculate the value of colours required to tranition to the new state
 * @return void
 */

void transition_state(uint8_t previousState)
   {
   	if(previousState==START)
   	{
   		redValue=STOP_RED_VALUE;
   		greenValue=STOP_GREEN_VALUE;
   		blueValue=STOP_BLUE_VALUE;
   	}
   	if(previousState==TRANSITION_TO_CROSSWALK)
   	{
   		redValue = (( CROSSWALK_RED_VALUE - redPreviousValue) * (0.0625*percentageIncrement)+ redPreviousValue ) ;
   		greenValue = ((CROSSWALK_GREEN_VALUE - greenPreviousValue) * (0.0625*percentageIncrement) + greenPreviousValue);
   		blueValue = ((CROSSWALK_BLUE_VALUE - bluePreviousValue) * (0.0625*percentageIncrement) + bluePreviousValue);
   		percentageIncrement++;
   	}
   	if(previousState==CROSSWALK)
   	{
   		redValue = (( GO_RED_VALUE - CROSSWALK_RED_VALUE) * (0.0625*percentageIncrement)+ CROSSWALK_RED_VALUE ) ;
   		greenValue = ((GO_GREEN_VALUE - CROSSWALK_GREEN_VALUE) * (0.0625*percentageIncrement) + CROSSWALK_GREEN_VALUE);
   		blueValue = ((GO_BLUE_VALUE - CROSSWALK_BLUE_VALUE) * (0.0625*percentageIncrement) + CROSSWALK_BLUE_VALUE);
   		percentageIncrement++;
   	}
   	if(previousState == STOP)
   	{
   		redValue = ((GO_RED_VALUE - STOP_RED_VALUE) * (0.0625*percentageIncrement)+ STOP_RED_VALUE) ;
   		greenValue = ((GO_GREEN_VALUE - STOP_GREEN_VALUE) * (0.0625*percentageIncrement) + STOP_GREEN_VALUE);
   		blueValue = ((GO_BLUE_VALUE - STOP_BLUE_VALUE) * (0.0625*percentageIncrement) + STOP_BLUE_VALUE);
   		percentageIncrement++;
   	}
   	if(previousState == GO)
   	{
   		redValue = ((WARNING_RED_VALUE - GO_RED_VALUE) * (0.0625*percentageIncrement)+ GO_RED_VALUE) ;
   		greenValue = ((WARNING_GREEN_VALUE - GO_GREEN_VALUE) * (0.0625*percentageIncrement) + GO_GREEN_VALUE);
   		blueValue = ((WARNING_BLUE_VALUE - GO_BLUE_VALUE) * (0.0625*percentageIncrement) + GO_BLUE_VALUE);
   		percentageIncrement++;
   	}
   	if(previousState == WARNING)
   	{
   		redValue = ((STOP_RED_VALUE - WARNING_RED_VALUE) * (0.0625*percentageIncrement)+ WARNING_RED_VALUE) ;
   		greenValue = ((STOP_GREEN_VALUE - WARNING_GREEN_VALUE) * (0.0625*percentageIncrement) + WARNING_GREEN_VALUE);
   		blueValue = ((STOP_BLUE_VALUE - WARNING_BLUE_VALUE) * (0.0625*percentageIncrement) + WARNING_BLUE_VALUE);
   		percentageIncrement++;
   	}
   	if(previousState == CROSSWALK_LED_ON)
   	{
   		redValue=CROSSWALK_RED_VALUE;
   		greenValue=CROSSWALK_GREEN_VALUE;
   		blueValue=CROSSWALK_BLUE_VALUE;
   	}
   	if(previousState == CROSSWALK_LED_OFF)
   	{
   		redValue=0;
   		greenValue=0;
   		blueValue=0;
   	}
   	start_transition(redValue,greenValue,blueValue);

   }
