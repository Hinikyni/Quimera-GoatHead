#ifndef QUIMERAPID_HPP
#define QUIMERAPID_HPP

namespace Quimera{
    class PID{

        private:

            volatile float _kP, _kI, _kD;
            volatile float _pidSetPoint = 0, 
                           _pidLastError = 0,
                           _pidIntError = 0;
            int _pinA, _pinB, _pinPWM;

        public:
            // Variables
            volatile bool _dir = true; //* True -> Forward / False -> Backward
            volatile unsigned long _lastTime = 0;
            volatile unsigned _pwmAtual = 0;
            // Methods
            PID(unsigned char pinA, unsigned char pinB,  unsigned char pinPWM, float Kp, float Ki, float Kd);
            float run(double);
            void controlMotor();
            void controlMotor(unsigned char);
            void setPoint(float);
    };
}

#endif