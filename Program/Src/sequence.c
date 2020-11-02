/*
 * sequence.c
 *
 *  Created on: 2020/10/10
 *      Author: Takeki Mukaida
 */

#include "stdio.h"
#include "declaration.h"

#define BIAS 50
#define L_C  (100 + BIAS)
#define L_B  (175 + BIAS)
#define L_A  (250 + BIAS)

void sequence(short adress, short phase, double *x, double *y) {

	double xp = 0, yp = 0;

	switch(adress) {
		case  3:	sequence_Li(phase, &xp, &yp);
		case 11:	sequence_Na(phase, &xp, &yp);
		case 19:	sequence_K (phase, &xp, &yp);
		case 38:	sequence_Sr(phase, &xp, &yp);
		case 56:	sequence_Ba(phase, &xp, &yp);
	}

	*x = xp;
	*y = xp;
}

void sequence_Li(short phase, double *x, double *y) {	//Robot01_Lithium //LEFT
	switch(phase) {
		case 0:		*x = 0;		*y = -BIAS;	break;	//reset
		case 1:		*x = 0;		*y = L_C;	break;
		case 2:		*x = 0;		*y = 0;		break;
		case 3:		*x = 0;		*y = 0;		break;
		case 4:		*x = 0;		*y = L_B;	break;
		case 5:		*x = 0;		*y = L_C;	break;
		case 6:		*x = 0;		*y = L_A;	break;
		case 7:		*x = 0;		*y = L_B;	break;
		default:	*x = 0;		*y = 0;		break;
	}
}

void sequence_Na(short phase, double *x, double *y) {	//Robot02_Natrium //CENTER
	switch(phase) {
		case 0:		*x = 0;		*y = -BIAS;	break;	//reset
		case 1:		*x = 0;		*y = 0;		break;
		case 2:		*x = 0;		*y = 0;		break;
		case 3:		*x = 0;		*y = L_A;	break;
		case 4:		*x = 0;		*y = 0;		break;
		case 5:		*x = 0;		*y = L_B;	break;
		case 6:		*x = 0;		*y = L_B;	break;
		case 7:		*x = 0;		*y = L_A;	break;
		default:	*x = 0;		*y = 0;		break;
	}
}

void sequence_K (short phase, double *x, double *y) {	//Robot03_Kalium //RIGHT
	switch(phase) {
		case 0:		*x = 0;		*y = -BIAS;	break;	//reset
		case 1:		*x = 0;		*y = 0;		break;
		case 2:		*x = 0;		*y = L_B;	break;
		case 3:		*x = 0;		*y = 0;		break;
		case 4:		*x = 0;		*y = L_B;	break;
		case 5:		*x = 0;		*y = L_A;	break;
		case 6:		*x = 0;		*y = L_C;	break;
		case 7:		*x = 0;		*y = L_B;	break;
		default:	*x = 0;		*y = 0;		break;
	}
}

void sequence_Sr(short phase, double *x, double *y) {	//Robot04_Strontium

}

void sequence_Ba(short phase, double *x, double *y) {	//Robot05_Barium

}

