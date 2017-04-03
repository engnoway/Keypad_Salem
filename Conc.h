#ifndef _CONC_H_
#define _CONC_H_

#define CONC(A7,A6,A5,A4,A3,A2,A1,A0) 		CONC_HELP(A7,A6,A5,A4,A3,A2,A1,A0)
#define CONC_HELP(A7,A6,A5,A4,A3,A2,A1,A0)	(0b##A7##A6##A5##A4##A3##A2##A1##A0)


#endif
