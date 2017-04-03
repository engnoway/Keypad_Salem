/*
 * Keypad_prog.c
 *
 *  Created on: Jul 28, 2016
 *      Author: mohamed
 */
#include "Conc.h"
#include "util.h"
#include "Types.h"
#include "Keypad_interfac.h"
#include "KEYPAD_Config.h"
#include "KEYPAD_Private.h"
#include "DIO_config.h"
#include "DIO_interface.h"
#include "DIO_private.h"

typedef union {
	struct {
		u16 Num1 :1;
		u16 Num2 :1;
		u16 Num3 :1;
		u16 Num4 :1;
		u16 Num5 :1;
		u16 Num6 :1;
		u16 Num7 :1;
		u16 Num8 :1;
		u16 Num9 :1;
		u16 Num10 :1;
		u16 Num11 :1;
		u16 Num12 :1;
		u16 Num13 :1;
		u16 Num14 :1;
		u16 Num15 :1;
		u16 Num16 :1;
	} SingleKey;
	u16 AllKeys;
} Keypad;

/*Comment!: KEYPAD Rows Pins*/
static const u8 KEYPAD_Rows[NumberOfRows] = { KEYPAD_ROW1_PIN, KEYPAD_ROW2_PIN, KEYPAD_ROW3_PIN, KEYPAD_ROW4_PIN };
/*Comment!: KEYPAD Columns Pins*/
static const u8 KEYPAD_Columns[NumberOfColumns] = { KEYPAD_COLUMN1_PIN, KEYPAD_COLUMN2_PIN, KEYPAD_COLUMN3_PIN, KEYPAD_COLUMN4_PIN };

/*Comment!: Initialization Function*/

extern void KEYPAD_voidInit(void) {
	//Keypad Initialization
	u8 ColumnRow_Index;

	/*
	 c1 , c2 , c3 , c4 Direction output
	 c1 , c2 , c3 , c4 Value high
	 r1 , r2 , r3 , r4 Direction input - pullup resistor
*/
	 for(ColumnRow_Index=0;ColumnRow_Index<4;ColumnRow_Index++)
	 {
	 //Intialization for Columns input and active pullup resistor
	 DIO_u8WritePinDir(KEYPAD_Columns[ColumnRow_Index], DIO_u8INPUT);
	 DIO_u8WritePinVal(KEYPAD_Columns[ColumnRow_Index], DIO_u8HIGH);
	 //Intialization for Rows
	 DIO_u8WritePinDir(KEYPAD_Rows[ColumnRow_Index], DIO_u8OUTPUT);
	 DIO_u8WritePinVal(KEYPAD_Rows[ColumnRow_Index], DIO_u8LOW);
	 }

}

/*void key_init()
{
	DIO_u8WritePortDir(DIO_u8PORT2,0xF0);
	DIO_u8WritePortVal(DIO_u8PORT2,0x0F);//active pullup on colmns


}*/



////////////////salem's function//////////////////////////////////
u8 get_key(void){

	unsigned char i,key=1;
	for(i=0;i<4;i++)
	{ //Loop for 4 rows
		*DIO_u8PORTC &=~(0x80>>i); //Make rows low one by one
		//CLRBIT(DIO_u8PORTC,Bit);
		if(!(*DIO_u8PINC & (1<<col1)))
		{ //check COL1
			while(!(*DIO_u8PINC & (1<<col1))); //wait for release
			return key; //return pressed key value
			}
		if(!(*DIO_u8PINC & (1<<col2))){ //Check COL2
			key += 1; //Second key pressed
			while(!(*DIO_u8PINC & (1<<col2))); //wait for release
			return key; //return key value
			}
		if(!(*DIO_u8PINC & (1<<col3))){ //Check COL3
			key += 2; //Third key pressed
			while(!(*DIO_u8PINC & (1<<col3))); //Wait for release
			return key; //Return value
			}
		if(!(*DIO_u8PINC & (1<<col4))){ //check COL4
			key += 3; //Fourth key pressed
			while(!(*DIO_u8PINC & (1<<col4))); //Wait for release
			return key; //Return key value
			}
				key +=4; //Next row
				*DIO_u8PORTC |= 0x80>>i; //make read row high again
				}
	return 0; //return false if no key pressed
	}
//////////////////////////////////////////////


/*Comment!: Function to Check Keypad Key with DEBOUNCING*/
static u8 KEYPAD_u8CheckSwitch(u8 Copy_u8RowIdx, u8 Copy_u8ColumnIdx, u8* Copy_u8PtrVal) {
	u8 Local_u8RetrunStatus = u8OK;
	//u8 Local_u8DelayCounter;
	if ((Copy_u8RowIdx > NumberOfRows)) {
		Local_u8RetrunStatus = u8ERROR;
	} else {
		u8 Local_u8KeyValue;
		static u8 Local_u8PressedCounter[NumberOfRows][NumberOfColumns] = { {0} };//maybe yeb2a just one counter
		static u8 Local_u8RealesedCounter[NumberOfRows][NumberOfColumns] = { {0} };
		static u8 Local_u8KeyState[NumberOfRows][NumberOfColumns] = { {KEYPAD_u8RELEASED_STATE} }; // for state machine
		static u8 Local_u8KeyPrevState[NumberOfRows][NumberOfColumns] = { {KEYPAD_u8KEY_RELEASED} }; //to remember the previous key state

		switch (Local_u8KeyState[Copy_u8RowIdx][Copy_u8ColumnIdx]) {

		case KEYPAD_u8RELEASED_STATE:
			//Local_u8KeyValue = digitalRead(KEYPAD_Rows[Copy_u8RowIdx]);
			DIO_u8ReadPinVal(KEYPAD_Rows[Copy_u8RowIdx], &Local_u8KeyValue);
			if (Local_u8KeyValue == KEYPAD_u8KEY_PRESSED) {
				Local_u8KeyState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8BOUNCING_STATE;
				*Copy_u8PtrVal = Local_u8KeyPrevState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8KEY_RELEASED;
			} else { //Local_u8Value==KEYPAD_u8KEY_RELEASED
				*Copy_u8PtrVal = Local_u8KeyPrevState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8KEY_RELEASED;
			}
			//Local_u8RetrunStatus = u8OK;
			break;


case KEYPAD_u8BOUNCING_STATE:
			DIO_u8ReadPinVal(KEYPAD_Rows[Copy_u8RowIdx], &Local_u8KeyValue);
			//Local_u8KeyValue = digitalRead(KEYPAD_Rows[Copy_u8RowIdx]);
			if (Local_u8KeyValue == KEYPAD_u8KEY_PRESSED) {
				Local_u8PressedCounter[Copy_u8RowIdx][Copy_u8ColumnIdx]++;
				Local_u8RealesedCounter[Copy_u8RowIdx][Copy_u8ColumnIdx] = 0;
				if (Local_u8PressedCounter[Copy_u8RowIdx][Copy_u8ColumnIdx] == KEYPAD_u8PRESSED_RELEASED_LEVEL) {
					Local_u8KeyState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8PRESSED_STATE;
				} else {
				}
			} else {  //Local_u8Value==KEYPAD_u8KEY_RELEASED
				Local_u8RealesedCounter[Copy_u8RowIdx][Copy_u8ColumnIdx]++;
				Local_u8PressedCounter[Copy_u8RowIdx][Copy_u8ColumnIdx] = 0;
				if (Local_u8RealesedCounter[Copy_u8RowIdx][Copy_u8ColumnIdx] == KEYPAD_u8PRESSED_RELEASED_LEVEL) {
					Local_u8KeyState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8RELEASED_STATE;
				} else {
				}
			}
			*Copy_u8PtrVal = Local_u8KeyPrevState[Copy_u8RowIdx][Copy_u8ColumnIdx];
			//Local_u8RetrunStatus = u8OK;
			break;
		case KEYPAD_u8PRESSED_STATE:
			DIO_u8ReadPinVal(KEYPAD_Rows[Copy_u8RowIdx], &Local_u8KeyValue);
			//Local_u8KeyValue = digitalRead(KEYPAD_Rows[Copy_u8RowIdx]);
			if (Local_u8KeyValue == KEYPAD_u8KEY_PRESSED) {
				*Copy_u8PtrVal = Local_u8KeyPrevState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8KEY_PRESSED;
			} else {
				Local_u8KeyState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8BOUNCING_STATE;
				*Copy_u8PtrVal = Local_u8KeyPrevState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8KEY_PRESSED;  //KEYPAD_u8KEY_PRESSED;
			}
			//Local_u8RetrunStatus = u8OK;
			break;
		default:
			Local_u8KeyState[Copy_u8RowIdx][Copy_u8ColumnIdx] = KEYPAD_u8RELEASED_STATE;
			*Copy_u8PtrVal = KEYPAD_u8KEY_RELEASED;
			//Local_u8RetrunStatus = u8OK;
			break;
		}
	}
	return Local_u8RetrunStatus;
}
/*Comment!: Initialization Function*/
extern u8 KEYPAD_u8Read(u8* Copy_u8PtrVal) {
	u8 Column_Index, Row_Index, Local_u8KeyValue;
	u8 Local_u8RetrunStatus = u8OK;
	static u16 KeysPrevState = 0; //0 RELEASED, 1 = PRESSED
	//u16 Keys = 0;
	u8 Keys = 0;
	for (Column_Index = 0; Column_Index < NumberOfColumns; Column_Index++) {

		DIO_u8WritePinVal(KEYPAD_Columns[Column_Index], DIO_u8LOW);

		for (Row_Index = 0; Row_Index < NumberOfRows; Row_Index++) {

			KEYPAD_u8CheckSwitch(Row_Index, Column_Index, &Local_u8KeyValue);

			if (Local_u8KeyValue == KEYPAD_u8KEY_PRESSED) //check a specific row
			{
				if ((KeysPrevState & (1 << (Row_Index * NumberOfRows + Column_Index))) == 0) { // to active the single mode
					//Keys |= (1 << (Row_Index * NumberOfRows + Column_Index)); // for u16 Keys
					Keys = (Row_Index * NumberOfRows + Column_Index + 1); // for u8
					KeysPrevState |= (1 << (Row_Index * NumberOfRows + Column_Index));
				}
			}
			else {
				KeysPrevState &= ~(1 << (Row_Index * NumberOfRows + Column_Index));
			}
		}
		DIO_u8WritePinVal(KEYPAD_Columns[Column_Index], DIO_u8HIGH);
	}
	*Copy_u8PtrVal = Keys;
	return Local_u8RetrunStatus;
}



