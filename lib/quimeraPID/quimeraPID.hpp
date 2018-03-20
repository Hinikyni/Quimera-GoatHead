#ifndef QUIMERAPID_HPP
#define QUIMERAPID_HPP

namespace Quimera{
    class PID{
        private:
            float _kP, _kI, _kD;
            float _pidSetPoint, 
                  _pidLastError = 0,
                  _pidIntError = 0;
        public:
            unsigned long _lastTime = 0;
            

            PID(int setPoint, float Kp, float Ki, float Kd);
            float compute(double);
            void ssetPoint(float pidSetPoint);
    };
}

#endif