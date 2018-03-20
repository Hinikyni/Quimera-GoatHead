#include <Arduino.h>
#include "quimeraPID.hpp"

Quimera::PID::PID(int pidSetPoint, float Kp, float Ki, float Kd){
    this->_pidSetPoint = pidSetPoint;
    this->_kP = Kp;
    this->_kI = Ki;
    this->_kD = Kd;
}

float Quimera::PID::compute(double input){
    float P,I,D;
    float pidError = this->_pidSetPoint - abs(input);
    this->_pidIntError += pidError;
    //float pidDifError = this->_pidLastError - pidError;
    //this->_pidLastError = pidError;
    unsigned long pidDeltaTime = (millis() - this->_lastTime)/1000.0;
    this->_lastTime = millis();

    P = (pidError)*this->_kP;
    I = this->_pidIntError*this->_kI*pidDeltaTime;
    //D = (pidDifError)*this->_kD/pidDeltaTime;

    return (P+I);
}

void Quimera::PID::ssetPoint(float pidSetPoint){
    this->_pidSetPoint = pidSetPoint;
}