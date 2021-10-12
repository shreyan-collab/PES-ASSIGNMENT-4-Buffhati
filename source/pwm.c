/**
 * @file    pwm.c
 * @brief   This source file consists function definitions of initializing of TPM modules
 * 			and updating Red, Blue, Green colours through PWM signal
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU Expresso IDE, KL25Z Freedom development board
 * @References
 * 1) Howdy's Presentation 10,13,14 - To set GPIO port as an input, statemachine, interrupts
 * https://canvas.colorado.edu/courses/75704/files/folder/Lectures
 * 2) Embedded Systems fundamentals with ARM Cortex-M based microcontroller by Alexander Dean
 */

#include <MKL25Z4.h>
#include <pwm.h>

#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)		// on port D

/*
 * @brief: Initializes the Timer PWM module 0 channel 1 connected to blue led (Port D 1)
 * @param: Loading the MOD value with 48000 for 500 Hz PWM frequency
 * @return:void
 */
void Init_Blue_LED_PWM(uint16_t period)
{
	// Enable clock to port D
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;;

	// Blue FTM0_CH1, Mux Alt 4
	// Set pin to FTMs
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(4);

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	TPM0->MOD = period-1;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM0->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 1 to edge-aligned low-true PWM
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	TPM0->CONTROLS[1].CnV = 0;
	// Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}


/*
 * @brief: Initializes the Timer PWM module 2 channel 0 connected to red led (Port B 18)
 * @param: Loading the MOD value with 48000 for 500 Hz PWM frequency
 * @return:void
 */

void Init_Red_LED_PWM(uint16_t period)
{
	// Enable clock to port D
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;

		// Blue FTM0_CH1, Mux Alt 4
		// Set pin to FTMs
		PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
		PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(3);

		// Configure TPM
		SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
		//set clock source for tpm: 48 MHz
		SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
		//load the counter and mod
		TPM2->MOD = period-1;
		//set TPM count direction to up with a divide by 2 prescaler
		TPM2->SC =  TPM_SC_PS(1);
		// Continue operation in debug mode
		TPM2->CONF |= TPM_CONF_DBGMODE(3);
		// Set channel 1 to edge-aligned low-true PWM
		TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
		// Set initial duty cycle
		TPM2->CONTROLS[0].CnV = 0;
		// Start TPM
		TPM2->SC |= TPM_SC_CMOD(1);
}

/*
 * @brief: Initializes the Timer PWM module 2 channel 1 connected to green led (Port B 19)
 * @param: Loading the MOD value with 48000 for 500 Hz PWM frequency
 * @return:void
 */
void Init_Green_LED_PWM(uint16_t period)
{
	// Enable clock to port D
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;

		// Blue FTM0_CH1, Mux Alt 4
		// Set pin to FTMs
		PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
		PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(3);

		// Configure TPM
		SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
		//set clock source for tpm: 48 MHz
		SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
		//load the counter and mod
		TPM2->MOD = period-1;
		//set TPM count direction to up with a divide by 2 prescaler
		TPM2->SC =  TPM_SC_PS(1);
		// Continue operation in debug mode
		TPM2->CONF |= TPM_CONF_DBGMODE(3);
		// Set channel 1 to edge-aligned low-true PWM
		TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
		// Set initial duty cycle
		TPM2->CONTROLS[1].CnV = 0;
		// Start TPM
		TPM2->SC |= TPM_SC_CMOD(1);

}

/*
 * @brief: Updating the on-board Red, Blue, Green colors through PWM signal
 *
 * According to the state machine, the red, blue, green values are updated according to
 * the PWM frequency and multiplied with 0xFF for more led brightness
 *
 * @param1: Red value to be loaded with TPM 2 Channel 0 ranging from 0-255
 * @param2: Green value to be loaded with TPM 2 Channel 1 ranging from 0-255
 * @param3: Blue value to be loaded with TPM 0 Channel 1 ranging from 0-255
 * @return:void
 */

void start_transition(uint16_t redValue1,uint16_t greenValue1,uint16_t blueValue1)
   {
   	TPM2->CONTROLS[0].CnV = redValue1 * 0xFF;
   	TPM2->CONTROLS[1].CnV = greenValue1 * 0xFF;
   	TPM0->CONTROLS[1].CnV = blueValue1 * 0xFF;
   }
