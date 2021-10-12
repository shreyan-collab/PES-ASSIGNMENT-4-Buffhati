/**
 * @file    statemachine.h
 * @brief   This header file consists of function prototypes which executes the
 * 			 traffic light sequence with cross-walk functionality
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU Expresso IDE, KL25Z Freedom development board
 * @References
 * 1) Howdy's Presentation 10,13,14 - To set GPIO port as an input, statemachine, interrupts
 * https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 * 2) Embedded Systems fundamentals with ARM Cortex-M based microcontroller by Alexander Dean
 */
#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_



#endif /* STATEMACHINE_H_ */

 #include "MKL25Z4.h"


/*
 * @brief The red, green and blue values to be loaded with TPM modules is calculated
 * 		  depending on the states
 *
 * @param previous State to calculate the value of colours required to transition to the new state
 * @return void
 */

void set_led_colour(uint8_t previousState);


/*
 * @brief Executes the traffic light sequence with cross-walk functionality
 *
 * The traffic light sequence consists of 9 states including STOP, GO, WARNING states
 * with cross-walk state triggered through touch slider or gpio push button
 *
 * @return void
 */
void statemachine();

/*
 * @brief Check whether touch slider or switch is pressed to implement cross-walk functionality
 *
 *
 * @return true if slider/switch is pressed else return false
 */
bool check_button_pressed();
