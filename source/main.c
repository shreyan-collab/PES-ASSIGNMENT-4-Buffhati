
/**
 * @file    main.c
 * @brief   This source file consists of initializing of various modules and function call for
 * 			state machine
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU Expresso IDE, KL25Z Freedom development board
 * @References
 * 1) Howdy's Presentation 10,13,14 - To set GPIO port as an input, statemachine, interrupts
 * https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 * 2) Embedded Systems fundamentals with ARM Cortex-M based microcontroller by Alexander Dean
 */

#include <pwm.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdbool.h>
#include "touchslider.h"
#include "switch.h"
#include "timer.h"
#include "statemachine.h"
#include "log.h"

/*
 * @brief The main function initializes various modules and calls the state machine
 *
 * Initialization of various modules including timer, PWM, slider and switch
 * connected to gpio port is carried out
 *
 *
 * @return void
 */

int main(void)
{
  	/*Initialize board hardware, Auto Generated Code */
    BOARD_InitBootPins(); /*Configures pin routing and optionally pin electrical features*/
    BOARD_InitBootClocks(); /*Initialize clock divider registers and setting up oscillators*/
    BOARD_InitBootPeripherals(); /*Set up and initialize all required blocks and functions
    							 related to the peripherals hardware*/
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();  /* Initialize FSL debug console. */
#endif


    /*
     * @brief: Initializes the Timer PWM module 2 channel 0 connected to red led (Port B 18)
     * @param: Loading the MOD value with 48000 for 500 Hz PWM frequency
     * @return:void
     */
    Init_Red_LED_PWM(PWM_PERIOD);
    /*
     * @brief: Initializes the Timer PWM module 2 channel 1 connected to green led (Port B 19)
     * @param: Loading the MOD value with 48000 for 500 Hz PWM frequency
     * @return:void
     */
    Init_Green_LED_PWM(PWM_PERIOD);

    /*
     * @brief: Initializes the Timer PWM module 0 channel 1 connected to blue led (Port D 1)
     * @param: Loading the MOD value with 48000 for 500 Hz PWM frequency
     * @return:void
     */
    Init_Blue_LED_PWM(PWM_PERIOD);

    /*
     * @brief: Initializes the Systick timer Module with external clock frequency
     *
     * @return:void
     */
    Init_SysTick();

    /*
     * @brief Initializing the capacitive touch slider present on the hardware board
     *
     * @return void
     */
    Touch_Init();

    /*
     * @brief Initializes the switch connected to PORTD 3 pin
     *
     * @return void
     */
    init_switch();
    LOG("\nMain loop is starting");

    /*
     * @brief Executes the traffic light sequence with cross-walk functionality
     *
     * @return void
     */
    statemachine();

    return 0;
}




