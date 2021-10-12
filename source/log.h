/**
 * @file    log.h
 * @brief   This header file consists of a log function which prints debug messages to UART console
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU expresso IDE, KL25Z Freedom development board
 * @References
 * 1) Howdy's Presentation 10 - use of log.h in debug mode
 * https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 */




#ifndef LOG_H_
#define LOG_H_


#include <stdio.h>

#ifdef DEBUG
#  define LOG printf
#else
#  define LOG(...)
#endif



#endif /* LOG_H_ */
