/*
 * Keypad_config.h
 *
 *  Created on: Jul 28, 2016
 *      Author: mohamed
 */

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/*******************************************************/
/**************** Public Definitions *******************/
/*******************************************************/

/*Comment!: Switch State*/
/*Range!: DIO_u8LOW or DIO_u8HIGH*/
#define	KEYPAD_u8KEY_PRESSED	DIO_u8LOW //Low for pull up resistor & High for pull down resistor
#define	KEYPAD_u8KEY_RELEASED	DIO_u8HIGH

#define KEYPAD_u8PRESSED_RELEASED_LEVEL 10			//30

/*Comment!: KeyPad Configuration Num of Rows & Num of Cols*/
#define NumberOfRows	4
#define NumberOfColumns	4

#define Button2  7
#define Button3  3
#define Button4  4
#define Button5  5


#define col1 0
#define col2 1
#define col3 2
#define col4 3
/*Comment!: Switch Pin Configuration*/
/*Range!  : DIO_u8PIN0 : DIO_u8PIN31*/
#define KEYPAD_ROW1_PIN 		DIO_u8PIN20
#define KEYPAD_ROW2_PIN         DIO_u8PIN21
#define KEYPAD_ROW3_PIN         DIO_u8PIN22
#define KEYPAD_ROW4_PIN         DIO_u8PIN23
#define KEYPAD_COLUMN1_PIN      DIO_u8PIN16
#define KEYPAD_COLUMN2_PIN      DIO_u8PIN17
#define KEYPAD_COLUMN3_PIN      DIO_u8PIN18
#define KEYPAD_COLUMN4_PIN      DIO_u8PIN19
/*Comment!: if you want to change the keypad Configuration to be 5*5 just edit the NumberOfRows, NumberOfColumns to be 5 and add another #define with the number of extra row, col like #define KEYPAD_ROW5        DIO_u8PIN3 , #define KEYPAD_COLOUMN5     DIO_u8PIN7*/

#endif /* KEYPAD_CONFIG_H_ */
