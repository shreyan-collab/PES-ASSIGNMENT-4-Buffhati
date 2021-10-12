/**
 * @file    touchslider.h
 * @brief   This header file consists of function prototypes to calculate slider's input raw value
 * 			which is passed to the calling function to implement cross walk functionality in state machine
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU expresso IDE, KL25Z Freedom development board
 * @References
 *1) https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 */

#ifndef TOUCHSLIDER_H_
#define TOUCHSLIDER_H_

#include<stdio.h>
#include<stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"



/**
 * @brief To return the value of the touch slider's input
 *
 * Scanning can be done from two ways, one from low to high (Left to right slider and vice versa)
 * In this case, we are choosing slider 10 where capacitance will increase from left to right
 *
 * @return the raw value of the capacitive slider
 */
int Touch_Scan_LH(void);

/**
 * @brief Initializing the capacitive touch slider's input
 * connected in channel 9 and 10 of KL-25Z development board
 *
 * @return void
 */
void Touch_Init();

#endif /* TOUCHSLIDER_H_ */
