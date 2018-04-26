#include <Arduino.h>
#include "quimeraPID.hpp"

Quimera::PID::PID(unsigned char pinA, unsigned char pinB,  unsigned char pinPWM, float Kp, float Ki, float Kd){
    this->_kP = Kp;
    this->_kI = Ki;
    this->_kD = Kd;
    this->_pinA = _pinA;
    this->_pinB = _pinB;
    this->_pinPWM = _pinPWM;
}

float Quimera::PID::run(double input){
    
    if(!this->_pidSetPoint) {
        this->controlMotor();
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
    this->_pwmAtual = constrain(this->_pwmAtual, 0, 255);
    this->controlMotor(this->_pwmAtual); //TODO: Take it off and call isolated on main program
    return (PIDR); // Return the value of current PWM
}

void Quimera::PID::setPoint(float pidSetPoint){ //Set the Reference to PID
    if(pidSetPoint > 0){
        this->_dir = true; // Forward
    } else {
        this->_dir = false; // Going Back    
    }
    this->_pidSetPoint = abs(pidSetPoint);
}

void Quimera::PID::controlMotor(){
    digitalWrite(_pinA, HIGH); 
    digitalWrite(_pinB, HIGH);
}

void Quimera::PID::controlMotor(unsigned char PWM){ //!Execute the Action of PID

//* Orientation settings
    digitalWrite(_pinA, this->_dir); 
    digitalWrite(_pinB, !this->_dir);

//* Speed settings
    analogWrite(this->_pinPWM, PWM);
}