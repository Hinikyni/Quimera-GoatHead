#include <main.hpp>
#include <Arduino.h>
//#include <digitalWriteFast.h>   // library for high performance reads and writes by jrraines
                                // see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
                                // and http://code.google.com/p/digitalwritefast/


void setup() 
{
  SetupEncoders();
  Serial.begin(115200);
}

void loop() 
{
  Serial.print ("L\t");
  Serial.println (left_encoder_position);
  Serial.print ("R\t");
  Serial.println (right_encoder_position);
  delay(20);
}

void SetupEncoders()
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

void SetupMotors()
{
  pinMode(left_motor_enable_pin, OUTPUT);
  digitalWrite(left_motor_enable_pin, HIGH);
  pinMode(left_motor_direction_pin, OUTPUT);
  digitalWrite(left_motor_direction_pin, LOW);
  pinMode(left_motor_pwm_pin, OUTPUT);
  digitalWrite(left_motor_pwm_pin, LOW);
  pinMode(right_motor_enable_pin, OUTPUT);
  digitalWrite(right_motor_enable_pin, HIGH);
  pinMode(right_motor_direction_pin, OUTPUT);
  digitalWrite(right_motor_direction_pin, LOW);
  pinMode(right_motor_pwm_pin, OUTPUT);
  digitalWrite(right_motor_pwm_pin, LOW);
}