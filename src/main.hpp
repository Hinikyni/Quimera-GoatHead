#ifndef MAIN_HPP_
#define MAIN_HPP_

/*  Library for high performance reads and writes by jrraines
*   see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
*   and http://code.google.com/p/digitalwritefast/
*/
//#include <digitalWriteFast.h>   

/* Constants */
#define LOOP_TIME 100000 // 100 ms control loop.
const float l_wheels = 0.12; // Distance between wheels.
const float left_wheel_radius = 0.05225, right_wheel_radius = 0.05225; // Really! My robot has slightly different wheels.
const int encoder_cpr = 300; // Encoder counts per revolution\. I am using a HKT22 model.
const int gear_relationship = 3; // 3 encoder revolutions per wheel revolution.
const float pi = 3.14159265359;

// Outputs Pins definition
const unsigned int left_motor_enable_pin = 4;
const unsigned int left_motor_direction_pin = 5;
const unsigned int left_motor_pwm_pin = 6;
const unsigned int right_motor_enable_pin = 9;
const unsigned int right_motor_direction_pin = 10;
const unsigned int right_motor_pwm_pin = 11;
const unsigned int buzzer_pin = 12;

/* Digital Inputs definition */
const unsigned int left_encoder_a_pin = 2;
const unsigned int left_encoder_b_pin = 3;
const unsigned int right_encoder_a_pin = 20;
const unsigned int right_encoder_b_pin = 21;

/* Analog Inputs definition */
const unsigned int left_front_corner_sensor_pin = 0;
const unsigned int right_front_corner_sensor_pin = 1;
const unsigned int left_rear_corner_sensor_pin  = 2;
const unsigned int Right_rear_corner_sensor_pin = 3;
const unsigned int battery_voltage_pin = 4;
const unsigned int battery_current_pin = 5;

/* Interrupts definition */
const int left_encoder_a_interrupt = 3;
const int left_encoder_b_interrupt = 2;
const int right_encoder_a_interrupt = 0;
const int right_encoder_b_interrupt = 1;

/* Other variables */
volatile long left_encoder_position = 0;
volatile long right_encoder_position = 0;
volatile bool left_encoder_past_b = false;
volatile bool right_encoder_past_b = false;
enum motorstatus {ON = 0, OFF};
volatile int motor_status = OFF;
volatile long loop_time = 0;
double left_input, left_output, left_setpoint, right_input, right_output, right_setpoint = 0;
std_msgs::Float32 left_wheel_vel;
std_msgs::Float32 right_wheel_vel;
std_msgs::Float32 right_wheel_vel_real;
geometry_msgs::Twist sensor_vel;

/* PID objects */
//PID leftPID(&left_input, &left_output, &left_setpoint, Kp, Ki, Kd, DIRECT);
//PID rightPID(&right_input, &right_output, &right_setpoint, Kp, Ki, Kd, DIRECT);

/* Function protitypes~~'a'a*/
void controlLoop();
void setupEncoders();
void doLeftEncoderA();
void doLeftEncoderB();
void doRightEncoderA();
void doRightEncoderB();
void setupMotors();
void moveLeftMotorCB(const std_msgs::Int16& msg);
void moveRightMotorCB(const std_msgs::Int16& msg);
int averageAnalog(int pin);
int motorStatus();
int motorStatus(int status);
void bipGen (unsigned int sound_freq, unsigned long time_on, unsigned long period, unsigned int n_cycles);
void cmdVelCB( const geometry_msgs::Twist& twist);
#endif  // MAIN_HPP_