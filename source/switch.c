/**
 * @file    switch.c
 * @brief   This source file consists of function definition to configure the switch as
 * 			input, to check whether button is pressed, and the IRQ handler for switch when pressed
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU Expresso IDE, KL25Z Freedom development board
 * @References
 * 1) Howdy's Presentation 10,13,14 - To set GPIO port as an input, statemachine, interrupts
 * https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 * 2) Embedded Systems fundamentals with ARM Cortex-M based microcontroller by Alexander Dean
 */

#include <stdbool.h>
#include "MKL25Z4.h"
#include "switch.h"


#define SWITCH_GPIO_PORT GPIOD
#define SWITCH_PIN 3
#define SWITCH_PIN_CTRL_REG PORTD->PCR[SWITCH_PIN]
#define SWITCH_SCGC5_MASK SIM_SCGC5_PORTD_MASK
#define SWITCH_ISFR PORTD->ISFR


static int interrupt_triggered = 0;

/*
 * @brief Initialize the on-board switch to trigger cross-walk state of KL25Z freedom development board
 *
 * The GPIO Port D 3rd pin is configured as input with pull-up functionality to trigger
 * cross-walk when button is presses
 *
 * @return void
 */

void init_switch()
{
  SIM->SCGC5 |= SWITCH_SCGC5_MASK;
  SWITCH_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;
  SWITCH_PIN_CTRL_REG |= PORT_PCR_MUX(1);
  SWITCH_PIN_CTRL_REG |= PORT_PCR_PE(1) | PORT_PCR_PS(1);
  SWITCH_GPIO_PORT->PDDR &= ~(1 << SWITCH_PIN);
  SWITCH_PIN_CTRL_REG |=PORT_PCR_IRQC(8);
  NVIC_SetPriority (PORTD_IRQn, 4);
  NVIC_EnableIRQ(PORTD_IRQn);
  __enable_irq();
}

/*
 * @brief To check whether the button is pressed through interrupt
 *
 * When the interrupt is triggered, a flag is set which is stored in a local variable
 * before resetting the flag
 *
 * @return button_pressed - Sends 0 if button not pressed and 1 if button is pressed
 */
int check_button_pressed(void){
		uint32_t masking_state = __get_PRIMASK();
		__disable_irq();
		int button_pressed = interrupt_triggered;
		interrupt_triggered = 0;
		__set_PRIMASK(masking_state);
		return button_pressed;
}

/*
 * @brief Interrupt routine called when user presses the button connected to PORT D 3rd pin
 *
 * When the interrupt is triggered, a flag is set and the IFSR register is written 1 to
 * clear the interrupt which was set
 *
 * @return void
 */
void PORTD_IRQHandler(void){
	if ( ( (SWITCH_ISFR) & (1 << SWITCH_PIN) ) == 0)
		return;
	interrupt_triggered = 1;
	SWITCH_ISFR &= (1 << SWITCH_PIN);
}

