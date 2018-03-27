
#include <Arduino.h>
#include <ros.h>
#include <TimerThree.h>
#include <rosserial_arduino/Adc.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <quimeraPID.hpp>
#include <main.hpp>


//! ROS
ros::NodeHandle nh;
rosserial_arduino::Adc adc_msg;
ros::Publisher p("adc", &adc_msg);
std_msgs::Int16 infoMsg;
ros::Publisher info("info", &infoMsg);
ros::Subscriber<std_msgs::Float32> subCmdLeft("cmd_left_wheel", moveLeftMotorCB);
ros::Publisher left_wheel_vel_pub("/left_wheel_velocity", &left_wheel_vel);
ros::Subscriber<std_msgs::Float32> subCmdRight("cmd_right_wheel", moveRightMotorCB);
ros::Publisher right_wheel_vel_pub("/right_wheel_velocity", &right_wheel_vel);
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", cmdVelCB);
ros::Publisher sensor_vel_pub("/sensor_velocity", &sensor_vel);
ros::Publisher right_wheel_vel_pub_real("/right_wheel_velocity_real", &right_wheel_vel_real);


//! PID
Quimera::PID rightPID(right_motor_direction_pin, right_motor_pwm_pin, 155, 20, 0);
Quimera::PID leftPID(left_motor_direction_pin, left_motor_pwm_pin, 155, 20, 0);

void setup() 
{
  setupEncoders();
  setupMotors();
  Timer3.initialize(LOOP_TIME); /// Periodic Timer interrupt for control tasks.
  Timer3.attachInterrupt(controlLoop);
  nh.initNode();
  nh.advertise(p);
  nh.advertise(info);
  nh.subscribe(subCmdLeft);
  nh.advertise(left_wheel_vel_pub);
  nh.subscribe(subCmdRight);
  nh.advertise(right_wheel_vel_pub);
  nh.advertise(right_wheel_vel_pub_real);
  nh.subscribe(subCmdVel);
  nh.advertise(sensor_vel_pub);
  bipGen(800, 200, 333, 3); // Startup bips. It takes 1s.
}

void loop() 
{
  if (loop_time < millis()) // Melhorar: //! Podia ser Feito com Somente um Inteiro 
  {
    adc_msg.adc0 = averageAnalog(0); 
    adc_msg.adc1 = averageAnalog(1);
    adc_msg.adc2 = averageAnalog(2);
    adc_msg.adc3 = averageAnalog(3);
    adc_msg.adc4 = averageAnalog(4);
    adc_msg.adc5 = averageAnalog(5);
    p.publish(&adc_msg);
    loop_time = millis() + 1000; // 1 Hz analog data publishing.
  }
  nh.spinOnce();
}

void controlLoop()
{
  Timer3.detachInterrupt(); //stop the timer
  
  right_wheel_vel.data = float(right_encoder_position) * 2 * pi * right_wheel_radius * 1000000 / loop_time / gear_relationship / encoder_cpr;
  right_wheel_vel_pub.publish(&right_wheel_vel);
  
  right_wheel_vel_real.data = float(right_encoder_position) * 2 * pi * right_wheel_radius * 1000000 / LOOP_TIME / gear_relationship / encoder_cpr;
  right_wheel_vel_pub_real.publish(&right_wheel_vel_real);
  
  
  left_wheel_vel.data = float(left_encoder_position) * 2 * pi * left_wheel_radius * 1000000 / LOOP_TIME / gear_relationship / encoder_cpr;
  bool plot;
  if (left_wheel_vel.data <= 0) plot = false;
  left_wheel_vel.data = abs(left_wheel_vel.data);
  left_wheel_vel_pub.publish(&left_wheel_vel);
  if(!plot){
    left_wheel_vel.data *= -1;
  }

  sensor_vel.linear.x = (left_wheel_vel.data  + right_wheel_vel.data ) * 0.5; //! Nessa linha fizemos a consideraçao que os dois raios são iguais.
  sensor_vel.angular.z = (left_wheel_vel.data + right_wheel_vel.data)/l_wheels;
  
  sensor_vel.linear.y = 0;
  sensor_vel.linear.z = 0;
  sensor_vel.angular.x = 0;
  sensor_vel.angular.y = 0;
  
  sensor_vel_pub.publish(&sensor_vel);
  

  leftPID.run((double)left_wheel_vel.data);
  rightPID.run((double)right_wheel_vel_real.data);
 
  info.publish(&infoMsg);
  
  left_encoder_position = 0;
  right_encoder_position = 0;
  Timer3.attachInterrupt(controlLoop); //enable the timer
}

void setupEncoders()
{
  pinMode(left_encoder_a_pin, INPUT_PULLUP);
  pinMode(left_encoder_b_pin, INPUT_PULLUP);
  attachInterrupt(left_encoder_a_interrupt, doLeftEncoderA, RISING);
  attachInterrupt(left_encoder_b_interrupt, doLeftEncoderB, CHANGE);
  pinMode(right_encoder_a_pin, INPUT_PULLUP);
  pinMode(right_encoder_b_pin, INPUT_PULLUP);
  attachInterrupt(right_encoder_a_interrupt, doRightEncoderA, RISING);
  attachInterrupt(right_encoder_b_interrupt, doRightEncoderB, CHANGE);
}

void doLeftEncoderA()
{
  // Timer3.detachInterrupt();
  left_encoder_past_b ? left_encoder_position-- :  left_encoder_position++;
  // Timer3.attachInterrupt(ControlLoop);
}

void doLeftEncoderB()
{
  // Timer3.detachInterrupt();
  left_encoder_past_b = !left_encoder_past_b;
  // Timer3.attachInterrupt(ControlLoop);
}

void doRightEncoderA()
{
  // Timer3.detachInterrupt();
  right_encoder_past_b ? right_encoder_position++ :  right_encoder_position--;
  // Timer3.attachInterrupt(ControlLoop);
}

void doRightEncoderB()
{
  // Timer3.detachInterrupt();
  right_encoder_past_b = !right_encoder_past_b;
  // Timer3.attachInterrupt(ControlLoop);
}

void setupMotors()
{
  pinMode(left_motor_enable_pin, OUTPUT);
  pinMode(left_motor_direction_pin, OUTPUT);
  pinMode(left_motor_pwm_pin, OUTPUT);
  pinMode(right_motor_enable_pin, OUTPUT);
  pinMode(right_motor_direction_pin, OUTPUT);
  pinMode(right_motor_pwm_pin, OUTPUT);
  digitalWrite(left_motor_pwm_pin, LOW);
  digitalWrite(right_motor_pwm_pin, LOW);
  motor_status = motorStatus (ON);
}

int motorStatus()
{
  return motor_status;
}

int motorStatus(int status)
{
  digitalWrite(left_motor_enable_pin, status);
  digitalWrite(right_motor_enable_pin, status);
  return status;
}

void moveLeftMotorCB(const std_msgs::Float32& msg){
    leftPID.setPoint(msg.data);
}

void moveRightMotorCB(const std_msgs::Float32& msg){
    rightPID.setPoint(msg.data);
}

int averageAnalog(int pin){
  int v=0;
  for(int i=0; i<4; i++) v+= analogRead(pin);
  return v/4;
}


void bipGen (unsigned int sound_freq, unsigned long time_on, unsigned long period, unsigned int n_cycles)
{
  for (unsigned int i = 1; i <= n_cycles; i++)
    {
      tone(buzzer_pin, sound_freq, time_on);
      if (period > 0 && n_cycles > 0 && i < n_cycles)
      {
        delay(period);
      }
    }
}


void cmdVelCB( const geometry_msgs::Twist& twist)
{
  int gain = 4000;
  double left_wheel_data = (twist.linear.x - twist.angular.z*l_wheels);
  double right_wheel_data = (twist.linear.x + twist.angular.z*l_wheels);
  
  leftPID.setPoint(left_wheel_data.data);
  rightPID.setPoint(right_wheel_data.data);

}