#include <Arduino.h>
#include <ros.h>
#include <TimerThree.h>
#include <rosserial_arduino/Adc.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <PID_v1.h>
#include "main.hpp"

ros::NodeHandle nh; // Node Instance
rosserial_arduino::Adc adc_msg; //Instance Adc of serial_arduino, 6 int16.
ros::Publisher p("adc", &adc_msg); // Instance the Publisher to send msgs of the sensors (battery and line detector)
ros::Subscriber<std_msgs::Int16> subCmdLeft("cmd_left_wheel", moveLeftMotorCB); //Instantiate a subscriber of type Int16 in cmd_left_wheel and execute moveLeftMotorCB
ros::Publisher left_wheel_vel_pub("/left_wheel_velocity", &left_wheel_vel); // Instantiate a Publisher for left wheel vel
ros::Subscriber<std_msgs::Int16> subCmdRight("cmd_right_wheel", moveRightMotorCB); // Instantiate a Subscriber of cmd_right_wheel
ros::Publisher right_wheel_vel_pub("/nada", &right_wheel_vel); // Instantiate a Publisher to right wheel speed
ros::Publisher right_wheel_vel_pub_real("/right_wheel_velocity_real", &right_wheel_vel_real); // Instantiate a Publisher to right wheel speed
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", cmdVelCB); // Instantiate a subscriber at cmd_vel
ros::Publisher sensor_vel_pub("/sensor_velocity", &sensor_vel); // Instantiate a publisher of velocity sensor

PID leftWheelPID(&leftInput, &leftOutput, &leftSetpoint, KpL, KiL, KdL, DIRECT);
PID rightWheelPID(&rightInput, &rightOutput, &rightSetpoint, KpR, KiR, KdR, DIRECT);

void setup() 
{
  setupEncoders(); // Seta as variaveis dos Encoders
  setupMotors(); // Seta as variaveis do Motor

  leftWheelPID.setMode(AUTOMATIC); //* PID
  rightWheelPID.setMode(AUTOMATIC); 

  Timer3.initialize(LOOP_TIME); /// Periodic Timer interrupt for control tasks.
  Timer3.attachInterrupt(controlLoop); // Diz qual função será executada na interrupção

  nh.initNode(); // Inicia nó
  nh.advertise(p);  // Permite o Publisher escrever no topico
  nh.subscribe(subCmdLeft); // Começa a receber dados da velocidade da roda esquerda
  nh.advertise(left_wheel_vel_pub); // Permite o Publisher escrever no topico
  nh.advertise(right_wheel_vel_pub_real);
  nh.subscribe(subCmdRight); // Começa a receber dados da velocidade da roda direita
  nh.advertise(right_wheel_vel_pub); // Permite o Publisher escrever no topico
  nh.subscribe(subCmdVel); // Começa a receber dados da velocidade "total"
  nh.advertise(sensor_vel_pub); // Permite o Publisher escrever no topico

  bipGen(800, 200, 333, 3); // Startup bips. It takes 1s.
}

void loop() 
{
  if (loop_time < millis()) // Se o tempo de execução do arduino for maior que o tempo para entrada de loop
  {
    adc_msg.adc0 = leftOutput; // Retorna o valor medio da leitura analogica dos pinos analogicos 0~5 // "Linha"
    adc_msg.adc1 = averageAnalog(1); // Retorna o valor medio da leitura analogica dos pinos analogicos 0~5  // "Linha"
    adc_msg.adc2 = averageAnalog(2); // Retorna o valor medio da leitura analogica dos pinos analogicos 0~5  // "Linha"
    adc_msg.adc3 = averageAnalog(3); // Retorna o valor medio da leitura analogica dos pinos analogicos 0~5  // "Linha"
    adc_msg.adc4 = averageAnalog(4); // Retorna o valor medio da leitura analogica dos pinos analogicos 0~5  // Bateria
    adc_msg.adc5 = averageAnalog(5); // Retorna o valor medio da leitura analogica dos pinos analogicos 0~5  // Bateria
    p.publish(&adc_msg); // Publica em "adc" as informações dos sensores
    loop_time = millis() + 1000; // 1 Hz analog data publishing. //adiciona ao tempo de loop o tempo de execucao atual para entrar no proximo loop 
  }
  
  leftWheelPID.compute();
  rightWheelPID.compute();
  //if(!leftSetpoint) moveLeftMotor(constrain(leftOutput*650, 0, 254));
  nh.spinOnce(); // ros::spin()
}

void controlLoop()
{
  Timer3.detachInterrupt(); //stop the timer
  right_wheel_vel.data = float(abs(right_encoder_position)) * 20 * pi * right_wheel_radius / loop_time / (gear_relationship * encoder_cpr);
  right_wheel_vel_pub.publish(&right_wheel_vel); // Publica em right_wheel_vel a velocidade da roda esquerda calculada acima
  right_wheel_vel_real.data = float(right_encoder_position) * 2.0 * pi * right_wheel_radius * 1000000 / LOOP_TIME / gear_relationship / encoder_cpr; 
  right_wheel_vel_pub_real.publish(&right_wheel_vel_real);
  left_wheel_vel.data = left_encoder_position*2.0 * pi * left_wheel_radius * 1000000 / (LOOP_TIME * gear_relationship * encoder_cpr);
  left_wheel_vel_pub.publish(&left_wheel_vel); // Publica em left_wheel_vel a velocidade da roda esquerda calculada acima
  sensor_vel.linear.x = (left_wheel_vel.data + right_wheel_vel_real.data)/2;
  sensor_vel.linear.y = sensor_vel.linear.z = sensor_vel.angular.x = sensor_vel.angular.y = 0;
  sensor_vel.angular.z = (left_wheel_vel.data * left_wheel_radius + right_wheel_vel_real.data * right_wheel_radius)/l_wheels;
  sensor_vel_pub.publish(&sensor_vel); // Publica em sensor_vel as velocidades gerais do robo
  left_encoder_position = 0; // Seta a posição do encoder left para 0
  right_encoder_position = 0; // Seta a posição do encoder right para 0
  Timer3.attachInterrupt(controlLoop); //enable the timer
}

void setupEncoders() //Seta os Encoders
{
  pinMode(left_encoder_a_pin, INPUT_PULLUP);
  pinMode(left_encoder_b_pin, INPUT_PULLUP);
  attachInterrupt(left_encoder_a_interrupt, doLeftEncoderA, RISING); //interrompe se left_encoder_a_interrupt aumentar e chama a funão doLeftEncoderA
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

void setupMotors() // Seta as variaveis de motores
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

int motorStatus() // retorna o status do motor
{
  return motor_status;
}

int motorStatus(int status) // Altera o status do motor e retorna
{
  digitalWrite(left_motor_enable_pin, status);
  digitalWrite(right_motor_enable_pin, status);
  return status;
}

void moveLeftMotorCB(const std_msgs::Int16& msg) // Realiza a ação com os valores recebidos de cmd_vel_left
{
   leftSetpoint = msg.data;
  /*if (msg.data >=0 ) 
  {
    digitalWrite(left_motor_direction_pin, HIGH);
    analogWrite(left_motor_pwm_pin, msg.data); 
  }
  else
  {
    digitalWrite(left_motor_direction_pin, LOW);
    analogWrite(left_motor_pwm_pin, -msg.data);
  } */
}
void moveLeftMotor(short int leftVel) // Realiza a ação com os valores recebidos de cmd_vel_left
{
  if (leftVel >=0 ) 
  {
    digitalWrite(left_motor_direction_pin, HIGH);
    analogWrite(left_motor_pwm_pin, leftVel); 
  }
  else
  {
    digitalWrite(left_motor_direction_pin, LOW);
    analogWrite(left_motor_pwm_pin, -leftVel);
  }
}

void moveRightMotorCB(const std_msgs::Int16& msg) // Realiza a ação com os valores recebidos de cmd_vel_right
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

int averageAnalog(int pin){ // Faz a media dos valores recebidos dos pinos analogicos ( provavelmente: para obter um resultado mais confiavel )
  int v=0;
  for(int i=0; i<4; i++) v+= analogRead(pin);
  return v/4;
}

void bipGen (unsigned int sound_freq, unsigned long time_on, unsigned long period, unsigned int n_cycles) // Gera bips para o buzzer
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

void cmdVelCB( const geometry_msgs::Twist& twist) // Realiza as atividades com os valores recebidos do topico de velocide geral
{ // Comanda a velocidade das rodas
  int gain = 4000;
  float left_wheel_data = gain*(twist.linear.x - twist.angular.z*l_wheels);
  float right_wheel_data = gain*(twist.linear.x + twist.angular.z*l_wheels);
  
  if(right_wheel_data >= 0) // condição com right_wheel_data para controle de left_wheel_data 
  {
    digitalWrite(left_motor_direction_pin, HIGH);
    analogWrite(left_motor_pwm_pin, abs (left_wheel_data));
  }
  else
  {
    digitalWrite(left_motor_direction_pin, LOW);
    analogWrite(left_motor_pwm_pin, abs(left_wheel_data));
  }

  if(right_wheel_data >= 0)
  {
    digitalWrite(right_motor_direction_pin, HIGH);
    analogWrite(right_motor_pwm_pin, abs(right_wheel_data));
  }
  else
  {
    digitalWrite(right_motor_direction_pin, LOW);
    analogWrite(right_motor_pwm_pin, abs (right_wheel_data));
  }
}