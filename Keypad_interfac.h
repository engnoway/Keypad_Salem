/*
 * Kerypad_interfac.h
 *
 *  Created on: Jul 28, 2016
 *      Author: mohamed
 */

#ifndef KERYPAD_INTERFAC_H_
#define KERYPAD_INTERFAC_H_


/***************** Public Definitions ******************/
/*******************************************************/


/*******************************************************/
/*****************  Public Functions  ******************/
/*******************************************************/
typedef struct
{
	u16 SW1:1;
	u16 SW2:1;
	u16 SW3:1;
	u16 SW4:1;
	u16 SW5:1;
	u16 SW6:1;
	u16 SW7:1;
	u16 SW8:1;
	u16 SW9:1;
    u16 SW10:1;
    u16 SW11:1;
    u16 SW12:1;
    u16 SW13:1;
    u16 SW14:1;
    u16 SW15:1;
    u16 SW16:1;
}
FBF_Keypad;

/*Comment!: Initialization Function*/
extern void KEYPAD_voidInit(void);
/*Comment!: keypad_read Function*/
extern u8 KEYPAD_u8Read(u8* Copy_u8PtrVal);

extern u8 get_key(void);

#endif /* KERYPAD_INTERFAC_H_ */
