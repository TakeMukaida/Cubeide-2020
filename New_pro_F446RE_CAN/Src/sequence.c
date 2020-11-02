/*
 * sequence.c
 *
 *  Created on: 2020/10/10
 *      Author: Takeki Mukaida
 */

#include "stdio.h"
#include "declaration.h"

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

void sequence_Li(short phase, double *x, double *y) {	//Robot01_Lithium
	switch(phase) {
	case 0:
		//target_x = circular_orbit_radius * cos(circular_orbit_angle * M_PI / 180);
		//target_y = circular_orbit_radius * sin(circular_orbit_angle * M_PI / 180);
		//ramp = 1;
		//break;
	case 1:
		*x = 0;
		*y = 0;
		break;
	case 2:
		*x = -30;
		*y =   0;
		break;
	case 3:
		*x = 0;
		*y = -30;
		break;
	case 4:
		*x = -30;
		*y = -30;
		break;
	default:
		*x = 0;
		*y = 0;
	}
}

void sequence_Na(short phase, double *x, double *y) {	//Robot02_Natrium

}

void sequence_K (short phase, double *x, double *y) {	//Robot03_Kalium

}

void sequence_Sr(short phase, double *x, double *y) {	//Robot04_Strontium

}

void sequence_Ba(short phase, double *x, double *y) {	//Robot05_Barium

}

