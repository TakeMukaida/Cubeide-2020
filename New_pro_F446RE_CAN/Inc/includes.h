/*
 * includes.h
 *
 *  Created on: 2020/08/20
 *      Author: Takeki Mukaida
 */

#ifndef INC_INCLUDES_H_
#define INC_INCLUDES_H_

#define deg_to_rad(deg)	((deg / 360) * 2 * M_PI)

#define KP_X 5.5
#define KI_X 1.0
#define KD_X 0.00
#define KP_Y 5.5
#define KI_Y 1.0
#define KD_Y 0.00
#define KP_A 0.5
#define KI_A 0.0
#define KD_A 0.00

#define ROUND 8192
#define CONTROL_CYCLE 0.01	 	//10ms

#define WHEEL 			11.938   	//3.8*PI
#define ROBOT_RADIUS	8			//8cm

#define MAX 45 //app. under 100  6V (2cell)

#define M_ADDR_A (0x10 << 1)
#define M_ADDR_B (0x11 << 1)
#define M_ADDR_C (0x12 << 1)
//0x10 << 1 == 0001		//BisonMD - 1234 - Up1Down0
//0x11 << 1 == 1001
//0x12 << 1 == 0101
//0x13 << 1 == 1101

#define RECEIVE_BYTE 13
#define CHECK_BYTE 13

#endif /* INC_INCLUDES_H_ */
