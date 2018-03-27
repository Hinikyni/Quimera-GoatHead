#ifndef QUIMERAPID_HPP
#define QUIMERAPID_HPP

namespace Quimera{
    class PID{

        private:

            volatile float _kP, _kI, _kD;
            volatile float _pidSetPoint = 0, 
                           _pidLastError = 0,
                           _pidIntError = 0;
            volatile int _pwmAtual = 0;
            int _dirPin, _pwmPin;

        public:

            volatile bool _dir = true;
            volatile unsigned long _lastTime = 0;
            
            PID(unsigned int directionPin, unsigned int pwmPin, float Kp, float Ki, float Kd);
            float run(double);
            void controlMotor(unsigned int);
            void setPoint(float);
    };
}

#endif