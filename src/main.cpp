#include <Arduino.h>
#include <ros.h>
#include <rosserial_arduino/Adc.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>
#include <main.hpp>

ros::NodeHandle nh;

rosserial_arduino::Adc adc_msg;
ros::Publisher p("adc", &adc_msg);
ros::Subscriber<std_msgs::Int16> subCmdLeft("cmd_left_wheel", moveLeftMotorCB);
ros::Subscriber<std_msgs::Int16> subCmdRight("cmd_right_wheel", moveRightMotorCB);
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", cmdVelCB);

void setup() 
{
  setupEncoders();
  setupMotors();
  nh.initNode();
  nh.advertise(p);
  nh.subscribe(subCmdRight);
  nh.subscribe(subCmdLeft);
  bipGen(800, 200, 333, 3); // Startup bips. It takes 1s.
}

void loop() 
{
  if (loop_time < millis())
  {
    adc_msg.adc0 = averageAnalog(0); 
    adc_msg.adc1 = averageAnalog(1);
    adc_msg.adc2 = averageAnalog(2);
    adc_msg.adc3 = averageAnalog(3);
    adc_msg.adc4 = averageAnalog(4);
    adc_msg.adc5 = averageAnalog(5);
    p.publish(&adc_msg);
    loop_time = millis() + 1000;
  }
  nh.spinOnce();
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
  left_encoder_past_b ? left_encoder_position-- :  left_encoder_position++;
}

void doLeftEncoderB()
{
  left_encoder_past_b = !left_encoder_past_b;
}

void doRightEncoderA()
{
  right_encoder_past_b ? right_encoder_position++ :  right_encoder_position--;
}

void doRightEncoderB()
{
  right_encoder_past_b = !right_encoder_past_b;
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

void moveLeftMotorCB(const std_msgs::Int16& msg)
{
  if (msg.data >=0 )
  {
    digitalWrite(left_motor_direction_pin, HIGH);
    analogWrite(left_motor_pwm_pin, msg.data);
  }
  else
  {
    digitalWrite(left_motor_direction_pin, LOW);
    analogWrite(left_motor_pwm_pin, -msg.data);
  }
}

void moveRightMotorCB(const std_msgs::Int16& msg)
{
  if (msg.data >= 0)
  {
    digitalWrite(right_motor_direction_pin, HIGH);
    analogWrite(right_motor_pwm_pin, msg.data);
  }
  else
  {
    digitalWrite(right_motor_direction_pin, LOW);
    analogWrite(right_motor_pwm_pin, -msg.data);
  }
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
  float left_wheel_data = gain*(twist.linear.x - twist.angular.z*l_wheels);
  float right_wheel_data = gain*(twist.linear.x + twist.angular.z*l_wheels);
  
  if(right_wheel_data >= 0)
  {
    digitalWrite(left_motor_direction_pin, HIGH);
    analogWrite(left_motor_pwm_pin, abs (left_wheel_data));
  }
  else
  {
    digitalWrite(left_motor_direction_pin, LOW);
    analogWrite(left_motor_pwm_pin, abs (left_wheel_data));
  }

  if(right_wheel_data >= 0)
  {
    digitalWrite(right_motor_direction_pin, HIGH);
    analogWrite(right_motor_pwm_pin, abs (right_wheel_data));

  }
  else
  {
    digitalWrite(right_motor_direction_pin, LOW);
    analogWrite(right_motor_pwm_pin, abs (right_wheel_data));
  }
}