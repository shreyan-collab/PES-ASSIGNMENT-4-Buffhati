/**
 * @file    touchslider.c
 * @brief   This source file consists of function definitions to calculate slider's input raw value
 * 			which is passed to the calling function to implement cross walk functionality in state machine
 * @date 	10th October, 2021
 * @author 	Shreyan Prabhu
 * @Tools   MCU expresso IDE, KL25Z Freedom development board
 * @References
 *1) https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 */

#include<touchslider.h>

#define TOUCH_OFFSET (550)  /*The initial offset value to be subtracted*/
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)/*macro for extracting the count from data register*/

/**
 * @brief To return the value of the touch slider's input
 *
 * Scanning can be done from two ways, one from low to high (Left to right slider and vice versa)
 * In this case, we are choosing slider 10 where capacitance will increase from left to right
 *
 * @return the raw value of the capacitive slider
 */

int Touch_Scan_LH(void)
{
	unsigned int scan = 0;
	TSI0->DATA = 	TSI_DATA_TSICH(10u);/* Channel 10 is chosen where capacitance will increase from left to right*/
	TSI0->DATA |= TSI_DATA_SWTS_MASK; /*software trigger to start the scan*/
 	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )); /*waiting for the scan to complete 32 times*/
	scan = TOUCH_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; /*writing one to clear the end of scan flag*/
	return scan-TOUCH_OFFSET;/*The raw touch value of the capacitive slider */

}


/**
 * @brief Initializing the capacitive touch slider's input connected in channel 9 and 10 of KL-25Z development board
 *
 * @return void
 */
void Touch_Init()
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; /*enabling the clock*/

	TSI0->GENCS = TSI_GENCS_MODE(0u) | /*operating in non-noise mode*/
								TSI_GENCS_REFCHRG(0u) | /*reference oscillator charge and discharge value 500nA*/
								TSI_GENCS_DVOLT(0u) | /*oscillator voltage rails set to default*/
								TSI_GENCS_EXTCHRG(0u) | /*electrode oscillator charge and discharge value 500nA*/
								TSI_GENCS_PS(0u) |  /* frequency clcok divided by one */
								TSI_GENCS_NSCN(31u) | /*scanning the electrode 32 times */
								TSI_GENCS_TSIEN_MASK | /* enabling the TSI module */
								TSI_GENCS_EOSF_MASK; /* writing one to clear the end of scan flag */
}
