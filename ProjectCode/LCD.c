/******************************************************************************
 * Name:  			LCD.c  	
 * Description: This is used for configuration of the LCD screen. This is taken
 *							the 387 Lab. 
 * Version: 		Version 1.00
 * Authors: 		Gunjeet Dhaliwal | Mckenzie Busenius
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *          
 *****************************************************************************/


#include "LCD.h"
#include "stm32f10x.h"


void LCD_IO_INIT(void) {
		for(int i=0;i<4;i++)
			commandToLCD(LCD_8B2L);
		
		commandToLCD(LCD_DCB);
		commandToLCD(LCD_MCR);
		commandToLCD(LCD_CLR);	
}


void commandToLCD(uint8_t data) {
		GPIOB->BSRR = LCD_CM_ENA; //RS low, E high
		//GPIOC->ODR = data; //BAD: may affect upper bits on port C
		GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
		GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
		delay(8000);
		GPIOB->BSRR = LCD_CM_DIS; //RS low, E low
		delay(80000);
}


void delay(int count) {
		int i=0;
		
		for(i=0; i< count; ++i){
			//Empty Loop
		}
}


void dataToLCD(uint8_t data){
		GPIOB->BSRR = LCD_DM_ENA; //RS low, E high
		//GPIOC->ODR = data; //BAD: may affect upper bits on port C
		GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
		GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
		delay(8000);
		GPIOB->BSRR = LCD_DM_DIS; //RS low, E low
		delay(80000);
}


void to_ascii(int val) {
		if(val < 10)
			dataToLCD(val + 0x30);
		else 
			dataToLCD(val + 0x37);
}
