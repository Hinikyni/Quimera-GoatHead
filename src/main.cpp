#include <main.hpp>
#include <Arduino.h>
//#include <digitalWriteFast.h>   // library for high performance reads and writes by jrraines
                                // see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
                                // and http://code.google.com/p/digitalwritefast/


void setup() 
{
  setupEncoders();
  setupMotors();
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
  digitalWrite(left_motor_enable_pin, LOW);
  pinMode(left_motor_direction_pin, OUTPUT);
  digitalWrite(left_motor_direction_pin, LOW);
  pinMode(left_motor_pwm_pin, OUTPUT);
  digitalWrite(left_motor_pwm_pin, LOW);
  pinMode(right_motor_enable_pin, OUTPUT);
  digitalWrite(right_motor_enable_pin, LOW);
  pinMode(right_motor_direction_pin, OUTPUT);
  digitalWrite(right_motor_direction_pin, LOW);
  pinMode(right_motor_pwm_pin, OUTPUT);
  digitalWrite(right_motor_pwm_pin, LOW);
}

void moveLeftMotor(int left_pwm)
{
  if (left_pwm>=0)
  {
    digitalWrite(left_motor_direction_pin, HIGH);
    analogWrite(left_motor_pwm_pin, left_pwm);
  }
  else
  {
    digitalWrite(left_motor_direction_pin, HIGH);
    analogWrite(left_motor_pwm_pin, abs(left_pwm));
  }
}

void moveRightMotor(int right_pwm)
{
  if (right_pwm>=0)
  {
    digitalWrite(right_motor_direction_pin, HIGH);
    analogWrite(right_motor_pwm_pin, right_pwm);
  }
  else
  {
    digitalWrite(right_motor_direction_pin, HIGH);
    analogWrite(right_motor_pwm_pin, abs(rightt_pwm));
  }
}

int changeMotorState(motor, state)
{

}