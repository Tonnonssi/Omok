#include <Arduino.h>
#include <Wire.h>
#include "PCA9685.h" 
#include "control6DOF.h"

Control6DOF::Control6DOF(int input_pins[6]) {
    for (int i = 0; i < 6; ++i) { servo_pins[i] = input_pins[i]; } 
    Wire.begin();                // I2C 초기화
    pwmController.resetDevices(); // PCA9685 초기화
    pwmController.init();         // 기본 설정
    pwmController.setPWMFreqServo(); // PWM 주파수 설정 (50Hz)
}

void Control6DOF::setSpeed(int step_size, int speed_delay) {
    this->step_size = step_size;
    this->speed_delay = speed_delay;
}

void Control6DOF::showSpeedParams() {
    Serial.print(this->step_size);
    Serial.print(this->speed_delay);
}

void Control6DOF::rotateSingleJointTo(int joint_num, int joint_position) {
    int current_position = this->current_positions[joint_num];
    int target_position = clamp(joint_position, 0, 180);

    unsigned long current_time = millis();
    unsigned long last_updated_times = 0;

    if (current_time - last_updated_times >= this->speed_delay) {
        last_updated_times = current_time;

        if (current_position < target_position) {
            current_position += this->step_size;
            if (current_position > target_position) current_position = target_position;
        } else if (current_position > target_position) {
            current_position -= this->step_size;
            if (current_position < target_position) current_position = target_position;
        }

        int pulse_length = map(current_position, 0, 180, this->servo_min, this->servo_max);
        pwmController.setChannelPWM(joint_num, pulse_length);
        this->current_positions[joint_num] = current_position;
    }
}

void Control6DOF::rotateSingleJointBy(int joint_num, int joint_step) {
    int current_position = this->current_positions[joint_num];
    int target_position = current_position + joint_step;

    target_position = clamp(target_position, 0, 180); // 범위 안에 넣음 

    rotateSingleJointTo(joint_num, target_position);
    
}

void Control6DOF::rotateJointsTo(int active_joints_n, int joint_nums[], int joint_positions[]) {
    for (int i=0 ; i < active_joints_n; i++){
        rotateSingleJointTo(joint_nums[i], joint_positions[i]);
    }
}

void Control6DOF::rotateJointsBy(int active_joints_n, int joint_nums[], int joint_steps[]) {
    for (int i=0 ; i < active_joints_n; i++){
        rotateSingleJointBy(joint_nums[i], joint_steps[i]);
    }
}

void Control6DOF::resetPosition() {
    int joints[] = {0, 1, 2, 3, 4, 5};
    rotateJointsTo(6, joints, this->init_positions);
}

int Control6DOF::clamp(int value, int min_val, int max_val) {
    return (value < min_val) ? min_val : (value > max_val) ? max_val : value;
}