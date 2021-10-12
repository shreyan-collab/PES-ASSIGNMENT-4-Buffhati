/**
 * @file    timer.c
 * @brief   This source file consists of function definition to configure the systick module
 	 	 	systick interrupt and timer functions, used to calculate time in state machine
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU Expresso IDE, KL25Z Freedom development board
 * @References
 * 1) Howdy's Presentation 10,13,14 - To set GPIO port as an input, statemachine, interrupts
 * https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 * 2) Embedded Systems fundamentals with ARM Cortex-M based microcontroller by Alexander Dean
 */



#include <stdbool.h>
#include "timer.h"
#include "MKL25Z4.h"

bool flag=0;
volatile uint16_t checkTimeout=0;

ticktime transitionCount=0;
ticktime reset_time=0;


/*
 *@brief Initializing the capacitive touch slider present on the hardware board
 *
 *The clock is set as external clock and timer is incremented very 62.5ms and the NVIC
 *priority is set as 3
 *
 *@return void
 */
void Init_SysTick(void)
{
  	SysTick->LOAD = ((48000000L/16)/16);
  	NVIC_SetPriority(SysTick_IRQn,3);
  	SysTick->VAL=0;
  	SysTick->CTRL=SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk ;

}

/*
 *@brief The interrupt handler when the interrupt is triggered for 62.5 ms
 *
 *Ticks variable is incremented, a flag is set to 1 when 1 ms is reached
 *
 *@return void
 */
void SysTick_Handler()
{
   transitionCount++;
   checkTimeout=1;
   flag=1;

}

/*
 *@brief Time in msec since startup
 *
 *
 *@return time since startup in ticks to the calling function where every tick is 62.5 ms
 */

ticktime now()
{
	return transitionCount;
}

/*
 *@brief This function is used in conjunction with get_timer() function
 *		 to calculate the current time by subtracting the reset_time with now time
 *
 *
 *@return void
 */

void reset_timer()
{
	reset_time=now();
}

/*
 *@brief This function is used in conjunction with reset_timer() function
 *		 to calculate the current time by subtracting the reset_time with now time
 *
 *
 *@return the current time in ticks  to the calling function where every tick is 62.5 ms
 */
ticktime get_timer()
{
	return now()-reset_time;

}


