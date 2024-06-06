 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Author: Tarek Emad
 *
 *******************************************************************************/



#include<avr/io.h>
#include"adc.h"
#include"common_macros.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void ADC_init(const ADC_ConfigType* Config_Ptr)
{
    /* ADMUX Register Bits Description:
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 * Reference voltage bits are inserted according to the value in the structure
	 */
	ADMUX  |= ((Config_Ptr -> ref_volt) << 6);



    /* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * Prescalar bits are inserted according to the value in the structure
	 */
   // ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);

    ADCSRA |=   Config_Ptr -> prescaler;

    SET_BIT(ADCSRA,ADEN);
#if(ADC_INTERRUPT==1)
    SET_BIT(ADCSRA,ADIE);
#endif
}
#if (ADC_INTERRUPT==1)

volatile uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}

void ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
}
#else
uint16 ADC_readChannel(uint8 channel_num)
{
    channel_num &= 0x07; /* channel number must be from 0 --> 7 */
    ADMUX = (ADMUX & 0xE0) | (channel_num); /* choose the correct channel by setting the channel number in MUX4:0 bits */
    SET_BIT(ADCSRA,ADSC); /* start conversion write '1' to ADSC */
    while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* wait for conversion to complete ADIF becomes '1' */
    SET_BIT(ADCSRA,ADIF); /* clear ADIF by write '1' to it :) */
    return ADC; /* return the data register */
}
#endif
