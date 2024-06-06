 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Author: Tarek Emad
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_INTERRUPT 0 // mode for enabling and disabling interrupt in ADC Driver
#define ADC_MAX_VALUE 1023
#define ADC_REF_VOLTAGE 2.56

/*******************************************************************************
 *                                Enums                                        *
 *******************************************************************************/
typedef enum{
    AREF,AVCC,INTERNAL_VOLTAGE_REFERENCE = 3
}ADC_ReferenceVoltage;

typedef enum{
    Fcpu,div_by_2_2,div_by_4,div_by_8,div_by_16,div_by_32,div_by_64,div_by_128
}ADC_Prescaler;
/*******************************************************************************
 *                                Structures                                    *
 *******************************************************************************/
typedef struct{
    ADC_ReferenceVoltage ref_volt;
    ADC_Prescaler prescaler;
    }ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
#if (ADC_INTERRUPT==1)
/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;

void ADC_readChannel(uint8 channel_num);

#else
uint16 ADC_readChannel(uint8 channel_num);
#endif
#endif
