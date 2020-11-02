/*
#include "omni.h"
#include "main.h"

//omni3:目標座標角度[rad]、出力[m/s]、目標機体角度[rad]、現在機体角度[rad]
void omni(int target_c_angle,float power, short target_r_angle, int current_r_angle) {
    float ang_vel = (float)ang_vel_deg * M_PI / 180.0f;             //角速度
    float theta = gyro_degree * M_PI / 180.0f;                              //現在の角度

    float rad = (((float)degree) * M_PI / 180.0f);                  //進行角度deg→rad

    float vx = (float)power * cos(rad);                             //x成分
    float vy = (float)power * sin(rad);                             //y成分

    float vx_ = vx * cos(theta) - vy * sin(theta);                      //回転行列x　半時計回り
    float vy_ = vx * sin(theta) + vy * cos(theta);                      //回転行列y　半時計回り

    tire[0] = (float)(-vx_ + (ROBOT_RADIUS * ang_vel));                                //前
    tire[1] = (float)(((vx_ / 2.0f - (sqrt(3.0f) * vy_)) / 2) + (ROBOT_RADIUS * ang_vel));  //右後
    tire[2] = (float)(((vx_ / 2.0f + (sqrt(3.0f) * vy_)) / 2) + (ROBOT_RADIUS * ang_vel));  //左後
}
*/




