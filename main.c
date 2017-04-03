/*
 * main.c
 *
 *  Created on: Jul 28, 2016
 *      Author: mohamed
 */
/*
#include <avr/io.h> // Include file for AVR
#define keyport PORTC //Keypad Port
#define keyportddr DDRC //Data Direction Register
#define DIO_u8PINC PINC //Keypad Port Pins

#define col1 PC0 //Column1 PortA.0
#define col2 PC1 //Column2 PortA.1
#define col3 PC2 //Column3 PortA.2
#define col4 PC3 //Column4 PortA.3

#define TRUE 1
#define FALSE 0

unsigned char keyval; //A variable

void key_init()
{
	keyportddr = 0xF0;
	keyport = 0x0F;//active pullup on colmns
}


unsigned char get_key(){

	unsigned char i,key=1;
	for(i=0;i<4;i++)
	{ //Loop for 4 rows
		keyport &=~(0x80>>i); //Make rows low one by one
		if(!(DIO_u8PINC & (1<<col1)))
		{ //check COL1
			while(!(DIO_u8PINC & (1<<col1))); //wait for release
			return key; //return pressed key value
			}
		if(!(DIO_u8PINC & (1<<col2))){ //Check COL2
			key += 1; //Second key pressed
			while(!(DIO_u8PINC & (1<<col2))); //wait for release
			return key; //return key value
			}
		if(!(DIO_u8PINC & (1<<col3))){ //Check COL3
			key += 2; //Third key pressed
			while(!(DIO_u8PINC & (1<<col3))); //Wait for release
			return key; //Return value
			}
		if(!(DIO_u8PINC & (1<<col4))){ //check COL4
			key += 3; //Fourth key pressed
			while(!(DIO_u8PINC & (1<<col4))); //Wait for release
			return key; //Return key value
			}
				key +=4; //Next row
				keyport |= 0x80>>i; //make read row high again
				}
	return FALSE; //return false if no key pressed
	}


int main()
{
	char val=0;
	DDRA=255;
	PORTA=0;
	key_init();
	while(1)
	{
		val=get_key();

		switch(val)
		{
		case 1:
			PORTA=1;
					break;
		case 2:
			PORTA=2;
					break;
		case 3:
			PORTA=3;
					break;
		case 4:
			PORTA=4;
					break;
		case 5:
			PORTA=5;
					break;
		case 6:
			PORTA=6;
					break;
		case 7:
			PORTA=7;
					break;
		case 8:
			PORTA=8;
					break;
		case 9:
			PORTA=9;
					break;
		case 10:
			PORTA=10;
					break;
		case 11:
			PORTA=11;
					break;
		case 12:
			PORTA=12;
					break;
		case 13:
			PORTA=13;
					break;
		case 14:
			PORTA=14;
					break;
		case 15:
			PORTA=15;
					break;
		case 16:
			PORTA=15;
					break;
		}

	}
	return 0;
}

*/







///////////////////////////////////////////////////////////driver keypad salem
#include "Types.h"

#include "Conc.h"
#include "util.h"

#include "DIO_config.h"
#include "DIO_private.h"
#include "DIO_interface.h"

#include "KEYPAD_config.h"
#include "Keypad_interfac.h"




int main(void)
{

u8 val=0;

	//KEYPAD_u8Read(&x);
DIO_voidInit();

KEYPAD_voidInit();


	while(1)
	{
		val=get_key();

		switch(val)
				{
				case 1:
					DIO_u8WritePortVal(0,1);
					//*DIO_u8PORTA=0b00000001;
							break;
				case 2:
					DIO_u8WritePortVal(0,1);
							break;
			case 3:
				DIO_u8WritePortVal(0,0);
				break;
							/*
				case 4:
					*DIO_u8PORTA=0;
							break;
				case 5:
					*DIO_u8PORTA=0;
							break;
				case 6:
					*DIO_u8PORTA=0;
							break;
				case 7:
					*DIO_u8PORTA=0;
							break;
				case 8:
					*DIO_u8PORTA=0;
							break;
				case 9:
					*DIO_u8PORTA=0;
							break;
				case 10:
					*DIO_u8PORTA=0;
							break;
				case 11:
					*DIO_u8PORTA=0;
							break;
				case 12:
					*DIO_u8PORTA=0;
							break;
				case 13:
					*DIO_u8PORTA=0;
							break;
				case 14:
					*DIO_u8PORTA=0;
							break;
				case 15:
					*DIO_u8PORTA=0;
							break;
				case 16:
					*DIO_u8PORTA=0;
							break;*/

				}

	}

	return 0;
}
