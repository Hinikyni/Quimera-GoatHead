#ifndef MAIN_HPP_
#define MAIN_HPP_

// Outputs Pins definition
const int left_motor_enable_pin = 5;
const int left_motor_direction_pin = 6;
const int left_motor_pwm_pin = 7;
const int right_motor_enable_pin = 9;
const int right_motor_direction_pin = 10;
const int right_motor_pwm_pin = 11;
const int buzzer_pin = 12;

// Digital Inputs definition
const int left_encoder_a_pin = 2;
const int left_encoder_b_pin = 3;
const int right_encoder_a_pin = 20;
const int right_encoder_b_pin = 21;

// Analog Inputs definition
const int left_front_corner_sensor_pin = 0;
const int right_front_corner_sensor_pin = 1;
const int left_rear_corner_sensor_pin  = 2;
const int Right_rear_corner_sensor_pin = 3;
const int battery_voltage_pin = 4;
const int battery_current_pin = 5;

//Interrupts definition
const int left_encoder_a_interrupt = 3;
const int left_encoder_b_interrupt = 2;
const int right_encoder_a_interrupt = 0;
const int right_encoder_b_interrupt = 1;

//encoder variables
volatile long left_encoder_position = 0;
volatile long right_encoder_position = 0;
volatile bool left_encoder_past_b = false;
volatile bool right_encoder_past_b = false;

// Function protitypes
void setupEncoders();
void doLeftEncoderA();
void doLeftEncoderB();
void doRightEncoderA();
void doRightEncoderB();
void setupMotors();
void moveLeftMotor(int left_pwm);
void moveRightMotor(int right_pwm);
int averageAnalog(int pin);

#endif  // MAIN_HPP_