/**
 * @file    timer.h
 * @brief   This header file consists of function prototypes to configure the systick module
 	 	 	systick interrupt and timer functions, used to calculate time in state machine
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU Expresso IDE, KL25Z Freedom development board
 * @References
 * 1) Howdy's Presentation 10,13,14 - To set GPIO port as an input, statemachine, interrupts
 * https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 * 2) Embedded Systems fundamentals with ARM Cortex-M based microcontroller by Alexander Dean
 */



#ifndef TIMER_H_
#define TIMER_H_



#endif /* TIMER_H_ */

#include "MKL25Z4.h"

typedef uint32_t ticktime;

/*
 *@brief Initializes the systick to generate a tick every 62.5 ms
 *
 *The clock is set as external clock and timer is incremented very 62.5ms and the NVIC
 *priority is set as 3
 *
 *@return void
 */
void Init_SysTick(void);

/*
 *@brief Time in msec since startup
 *
 *
 *@return time in msec since startup to the calling function
 */
ticktime current_time();


/*
 *@brief Calculate the number of ticks since startup, used in functions reset_timer()
 *and get_timer() to calculate number of ticks at various intervals
 *
 *@return no of ticks since program startup to the calling function where every tick is 62.5 ms
 */
ticktime now();

/*
 *@brief This function is used in conjunction with get_timer() function
 *		 to calculate the current time by subtracting the reset_time with now time
 *
 *
 *@return void
 */
void reset_timer();


/*
 *@brief This function is used in conjunction with reset_timer() function
 *		 to calculate the current time by subtracting the reset_time with now() time
 *
 *
 *@return the current time in ticks  to the calling function where every tick is 62.5 ms
 */
ticktime get_timer();



