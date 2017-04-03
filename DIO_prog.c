/*
 * DIO_prog.c
 *
 *  Created on: Jan 27, 2016
 *      Author: 7ossam
 */
#include "Conc.h"
#include "util.h"
#include "Types.h"

#include "DIO_config.h"
#include "DIO_private.h"
#include "DIO_interface.h"


#define  PINC_DIR   DIO_u8PINC
#define  PORTC_OUT   DIO_u8PORTC

static volatile u8* const DIO_u8PORTADD[DIO_u8PORTSIZE]={DIO_u8PORTA,DIO_u8PORTB,DIO_u8PORTC,DIO_u8PORTD};
static volatile u8* const DIO_u8PINADD[DIO_u8PORTSIZE]={DIO_u8PINA,DIO_u8PINB,DIO_u8PINC,DIO_u8PIND};
static volatile u8* const DIO_u8DDRADD[DIO_u8PORTSIZE]={DIO_u8DDRA,DIO_u8DDRB,DIO_u8DDRC,DIO_u8DDRD};



/*Comment!: Initialization function */
void DIO_voidInit(void)
{
	//DETERMINING INPUT AND OUTPUT
	*DIO_u8DDRA =DIO_u8PORT0DIR;
	*DIO_u8DDRB=DIO_u8PORT1DIR;
	*DIO_u8DDRC=DIO_u8PORT2DIR;
	*DIO_u8DDRD=DIO_u8PORT3DIR;
	//DETERMINING LOW AND HIGH
	*DIO_u8PORTA  = (*DIO_u8PORTA &~*DIO_u8DDRA) | (DIO_u8PORT0DIR & DIO_u8PORT0INIT);
	*DIO_u8PORTB  = (*DIO_u8PORTB &~*DIO_u8DDRB)  | (DIO_u8PORT1DIR & DIO_u8PORT1INIT);
	*DIO_u8PORTC  = (*DIO_u8PORTC &~*DIO_u8DDRC) | (DIO_u8PORT2DIR & DIO_u8PORT2INIT);
	*DIO_u8PORTD = (*DIO_u8PORTD &~*DIO_u8DDRD) | (DIO_u8PORT3DIR & DIO_u8PORT3INIT);
	return;
}




/*Comment!: Read Port Value */
extern u8 DIO_u8ReadPortVal(u8 Copy_u8PortIdx,u8* Copy_u8PtrToVal)
{
	u8 Local_u8Error=u8OK;
	if(Copy_u8PortIdx >= DIO_u8PORTSIZE)
	{
		Local_u8Error=u8ERROR;
	}
	else
	{
		*Copy_u8PtrToVal=*(DIO_u8PINADD[Copy_u8PortIdx]);
	}
//	switch(Copy_u8PortIdx)
//	{
//	case DIO_u8PORT0:
//		*Copy_u8PtrToVal=PIN0;
//		break;
//	case DIO_u8PORT1:
//		*Copy_u8PtrToVal=PIN1;
//		break;
//	case DIO_u8PORT2:
//		*Copy_u8PtrToVal=PIN2;
//		break;
//	case DIO_u8PORT3:
//		*Copy_u8PtrToVal=PIN3;
//		break;
//	default:
//		Local_u8Error=u8ERROR;
//	}
	return Local_u8Error;
}


/*Comment!: Write Port Value */
extern u8 DIO_u8WritePortVal(u8 Copy_u8PortIdx,u8 Copy_u8PortVal)
{
	u8 Local_u8Error=u8OK;
	if(Copy_u8PortIdx>=DIO_u8PORTSIZE)
		{
			Local_u8Error = u8ERROR;
		}
	else
		{
			*(DIO_u8PORTADD[Copy_u8PortIdx]) = Copy_u8PortVal;
		}
//	switch(Copy_u8PortIdx)
//	{
//		case DIO_u8PORT0:
//			PORT0=Copy_u8PortVal;
//			break;
//		case DIO_u8PORT1:
//			PORT1=Copy_u8PortVal;
//			break;
//		case DIO_u8PORT2:
//			PORT2=Copy_u8PortVal;
//			break;
//		case DIO_u8PORT3:
//			PORT3=Copy_u8PortVal;
//			break;
//		default:
//			Local_u8Error=u8ERROR;
//	}
	return Local_u8Error;
}



/*Comment!: Read Pin Value */
extern u8 DIO_u8ReadPinVal(u8 Copy_u8PinIdx,u8* Copy_u8PtrToVal)
{
	u8 Local_u8Error=u8OK;
	u8 Local_u8PinNum=Copy_u8PinIdx % DIO_u8PINPERPORT;
	u8 Local_u8PortNum=(u8)(Copy_u8PinIdx / DIO_u8PINPERPORT);
	if(Copy_u8PinIdx>=DIO_u8PINSIZE)
		{
			Local_u8Error = u8ERROR;
		}
	else
		{
			*Copy_u8PtrToVal=GETBIT(*(DIO_u8PINADD[Local_u8PortNum]),Local_u8PinNum) ;
		}

//	switch((u8)Local_u8PortNum)
//		{
//			case DIO_u8PORT0:
//				*Copy_u8PtrToVal=GetBit(PIN0,Local_u8PinNum);
//				break;
//			case DIO_u8PORT1:
//				*Copy_u8PtrToVal=GetBit(PIN1,Local_u8PinNum);
//				break;
//			case DIO_u8PORT2:
//				*Copy_u8PtrToVal=GetBit(PIN2,Local_u8PinNum);
//				break;
//			case DIO_u8PORT3:
//				*Copy_u8PtrToVal=GetBit(PIN3,Local_u8PinNum);
//				break;
//			default:
//				Local_u8Error=u8ERROR;
//		}
	return Local_u8Error;
}


/*Comment!: Write Pin Value */
extern u8 DIO_u8WritePinVal(u8 Copy_u8PinIdx,u8 Copy_u8PinVal)
{
	u8 Local_u8Error=u8OK;
	u8 Local_u8PinNum=Copy_u8PinIdx % DIO_u8PINPERPORT;
	u8 Local_u8PortNum=(u8)(Copy_u8PinIdx / DIO_u8PINPERPORT);
	if(Copy_u8PinIdx>=DIO_u8PINSIZE)
		{
			Local_u8Error = u8ERROR;
		}
	else
		{
			ASSIGNBIT(*(DIO_u8PORTADD[Local_u8PortNum]),Local_u8PinNum,Copy_u8PinVal);
		}
//	switch((u8)Local_u8PortNum)
//		{
//			case DIO_u8PORT0:
//				AssignBit(PORT0,Local_u8PinNum,Copy_u8PinVal);
//				break;
//			case DIO_u8PORT1:
//				AssignBit(PORT1,Local_u8PinNum,Copy_u8PinVal);
//				break;
//			case DIO_u8PORT2:
//				AssignBit(PORT2,Local_u8PinNum,Copy_u8PinVal);
//				break;
//			case DIO_u8PORT3:
//				AssignBit(PORT3,Local_u8PinNum,Copy_u8PinVal);
//				break;
//			default:
//				Local_u8Error=u8ERROR;
//		}
		return Local_u8Error;
}


/*Comment!: Write Pin Direction */
extern u8 DIO_u8WritePinDir(u8 Copy_u8PinIdx,u8 Copy_u8PinDir)
{
	u8 Local_u8Error=u8OK;
	u8 Local_u8PinNum=Copy_u8PinIdx % DIO_u8PINPERPORT;
	u8 Local_u8PortNum=(u8)(Copy_u8PinIdx / DIO_u8PINPERPORT);
	if(Copy_u8PinIdx>=DIO_u8PINSIZE)
		{
			Local_u8Error = u8ERROR;
		}
	else
		{
			ASSIGNBIT(*(DIO_u8DDRADD[Local_u8PortNum]),Local_u8PinNum,Copy_u8PinDir);
		}
//	Copy_u8PinDir=DIO_u8PINMASK;
//	switch((u8)Local_u8PortNum)
//		{
//				case DIO_u8PORT0:
//					AssignBit(DDR0,Local_u8PinNum,Copy_u8PinDir);
//					break;
//				case DIO_u8PORT1:
//					AssignBit(DDR1,Local_u8PinNum,Copy_u8PinDir);
//					break;
//				case DIO_u8PORT2:
//					AssignBit(DDR2,Local_u8PinNum,Copy_u8PinDir);
//					break;
//				case DIO_u8PORT3:
//					AssignBit(DDR3,Local_u8PinNum,Copy_u8PinDir);
//					break;
//				default:
//					Local_u8Error=u8ERROR;
//		}
	return Local_u8Error;
}


/*Comment!: Write Port Direction */
extern u8 DIO_u8WritePortDir(u8 Copy_u8PortIdx,u8 Copy_u8PortDir)
{
	u8 Local_u8Error=u8OK;
	if(Copy_u8PortIdx>=DIO_u8PORTSIZE)
		{
			Local_u8Error = u8ERROR;
		}
	else
		{
			*(DIO_u8DDRADD[Copy_u8PortIdx]) = Copy_u8PortDir;
		}
//	switch(Copy_u8PortIdx)
//	{
//		case DIO_u8PORT0:
//			DDR0=Copy_u8PortDir;
//			break;
//		case DIO_u8PORT1:
//			DDR1=Copy_u8PortDir;
//			break;
//		case DIO_u8PORT2:
//			DDR2=Copy_u8PortDir;
//			break;
//		case DIO_u8PORT3:
//			DDR3=Copy_u8PortDir;
//			break;
//		default:
//			Local_u8Error=u8ERROR;
//	}
		return Local_u8Error;
}


/*Comment!: Read Pin Direction */
extern u8 DIO_u8ReadPinDir(u8 Copy_u8PinIdx,u8* Copy_u8PtrToDir)
{
	u8 Local_u8Error=u8OK;
	u8 Local_u8PinNum=Copy_u8PinIdx % DIO_u8PINPERPORT;
	u8 Local_u8PortNum=(u8)(Copy_u8PinIdx / DIO_u8PINPERPORT);
	if(Copy_u8PinIdx>=DIO_u8PINSIZE)
		{
			Local_u8Error = u8ERROR;
		}
	else
		{
			*Copy_u8PtrToDir=GETBIT(*(DIO_u8DDRADD[Local_u8PortNum]),Local_u8PinNum) ;
		}
//	switch((u8)Local_u8PortNum)
//		{
//		case DIO_u8PORT0:
//			*Copy_u8PtrToDir=GetBit(DDR0,Local_u8PinNum);
//			break;
//		case DIO_u8PORT1:
//			*Copy_u8PtrToDir=GetBit(DDR1,Local_u8PinNum);
//			break;
//		case DIO_u8PORT2:
//			*Copy_u8PtrToDir=GetBit(DDR2,Local_u8PinNum);
//			break;
//		case DIO_u8PORT3:
//			*Copy_u8PtrToDir=GetBit(DDR3,Local_u8PinNum);
//			break;
//		default:
//			Local_u8Error=u8ERROR;
//	}
	return Local_u8Error;
}


/*Comment!: Read Port Direction */
extern u8 DIO_u8ReadPortDir(u8 Copy_u8PortIdx,u8* Copy_u8PtrToDir)
{
	u8 Local_u8Error=u8OK;
	if(Copy_u8PortIdx >= DIO_u8PORTSIZE)
		{
			Local_u8Error=u8ERROR;
		}
	else
		{
			*Copy_u8PtrToDir=*(DIO_u8DDRADD[Copy_u8PortIdx]);
		}
//	switch(Copy_u8PortIdx)
//		{
//			case DIO_u8PORT0:
//				*Copy_u8PtrToDir=DDR0;
//				break;
//			case DIO_u8PORT1:
//				*Copy_u8PtrToDir=DDR1;
//				break;
//			case DIO_u8PORT2:
//				*Copy_u8PtrToDir=DDR2;
//				break;
//			case DIO_u8PORT3:
//				*Copy_u8PtrToDir=DDR3;
//				break;
//			default:
//				Local_u8Error=u8ERROR;
//		}
	return Local_u8Error;
}
