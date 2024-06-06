/*
 * main.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Tarek Emad
 */


/*******************************************************************************
                        Includes
 *******************************************************************************/
#include "gpio.h"
#include "lm35_sensor.h"
#include "lcd.h"
#include "motor.h"
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>

uint8 temp;
/*******************************************************************************
 *                      Function Prototype                                     *
 *******************************************************************************/
void Fan_Speed_Control(void);

int main(void)
{

	GPIO_setupPinDirection(PORTA_ID,PIN2_ID,PIN_INPUT);
	LCD_init();
	DcMotor_init();
	ADC_ConfigType Config ={INTERNAL_VOLTAGE_REFERENCE ,div_by_8};
	ADC_init(&Config);

	_delay_ms(100);
	LCD_displayStringRowColumn(0,4,"FAN IS ");
	LCD_displayStringRowColumn(1,4,"Temp. =   C");

	while(1){
		Fan_Speed_Control();
	}

}

void Fan_Speed_Control(void){
	temp=LM35_getTemperature();
	LCD_moveCursor(1,11);
	if(temp>100){
		LCD_intgerToString(temp);

	}
	else{
		LCD_intgerToString(temp);
		bLCD_displayCharacter(' ');
	}
	LCD_moveCursor(0,11);
	if(temp>=120){
		DcMotor_Rotate(MOTOR_clockwise,100);
		LCD_displayString("ON");
		LCD_displayCharacter(' ');
	}else if(temp>=90){
		DcMotor_Rotate(MOTOR_clockwise,75);
		LCD_displayString("ON");
		LCD_displayCharacter(' ');
	}else if(temp>=60){
		DcMotor_Rotate(MOTOR_clockwise,50);
		LCD_displayString("ON");
		LCD_displayCharacter(' ');
	}else if(temp>=30){
		DcMotor_Rotate(MOTOR_clockwise,25);
		LCD_displayString("ON");
		LCD_displayCharacter(' ');
	}else{
		DcMotor_Rotate(MOTOR_STOP,0);
		LCD_displayString("OFF");
		LCD_displayCharacter(' ');
	}
}
