#include <Arduino.h>
#include "quimeraPID.hpp"

Quimera::PID::PID(unsigned int dirPin, unsigned int pwmPin, float Kp, float Ki, float Kd){
    this->_kP = Kp;
    this->_kI = Ki;
    this->_kD = Kd;
    this->_dirPin = dirPin;
    this->_pwmPin = pwmPin;
}

float Quimera::PID::run(double input){
    if(!this->_pidSetPoint) {
        this->controlMotor(0);
        return (0);
    }
    float P,I,D, PIDR;

    float pidError = this->_pidSetPoint - abs(input); //* Proportional Action - 비례 *//
    
    unsigned long pidDeltaTime = (millis() - this->_lastTime)/1000;
    this->_lastTime = millis();


    if(!pidError) return(this->_pwmAtual);

    this->_pidIntError += pidError; //* Integral Action - 적분 *//

    float pidDifError = this->_pidLastError - pidError; //* Diferencial Action - 미분*//
    this->_pidLastError = pidError;

    P = (pidError) * this->_kP;
    I += this->_pidIntError * this->_kI * pidDeltaTime;
    D = (pidDifError) * this->_kD/pidDeltaTime;

    PIDR = P + I + D;

    this->_pwmAtual += PIDR; //Add to the Current PWM the PID set.
    this->_pwmAtual = abs(this->_pwmAtual);
    this->_pwmAtual = constrain(this->_pwmAtual, 40, 254);

    //!Execute the Action
    this->controlMotor(this->_pwmAtual);

    
    return (this->_pwmAtual); // Return the value of current PWM
}

void Quimera::PID::setPoint(float pidSetPoint){ //Set the Reference to PID
    if(pidSetPoint > 0){
        this->_dir = true;
    } else {
        this->_dir = false;
    }
    this->_pidSetPoint = abs(pidSetPoint);
}

void Quimera::PID::controlMotor(unsigned int PWM){ //!Execute the Action of PID

    digitalWrite(this->_dirPin, (int)this->_dir);
    analogWrite(this->_pwmPin, PWM);

}