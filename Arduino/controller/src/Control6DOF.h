#include <Arduino.h>
#include <Wire.h>
#include "PCA9685.h" 

#ifndef CONTROL6DOF_H
#define CONTROL6DOF_H

class Control6DOF {
private:
    PCA9685 pwmController;

    // 속도를 조절하는 파라미터
    int step_size = 1; 
    int speed_delay = 10; 

    int current_positions[6] = {0, 0, 0, 0, 0, 0};
    int init_positions[6] = {0, 0, 0, 0, 0, 0};
    unsigned long last_updated_times[6] = {0, 0, 0, 0, 0, 0};

    const int servo_min = 102; // 최소 펄스 (0도)
    const int servo_max = 512; // 최대 펄스 (180도)

    void rotateSingleJointTo(int joint_num, int joint_position);
    void rotateSingleJointBy(int joint_num, int joint_step);

    int clamp(int value, int min_val, int max_val);

public:
    Control6DOF(int input_pins[6]);

    int servo_pins[6]; // 6DOF의 서보 모터가 할당되는 핀 위치 

    // step size와 관련된 매서드
    void setSpeed(int step_size, int speed_delay); 
    void showSpeedParams();

    // rotate joint
    void rotateJointsTo(int active_joints_n, int joint_nums[], int joint_positions[]);
    void rotateJointsBy(int active_joints_n, int joint_nums[], int joint_steps[]);

    void resetPosition();

};

#endif