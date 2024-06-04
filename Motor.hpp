#pragma once
#define PI 3.14159265358979
class Motor{
    public:
        // return inaccuarrcy
        virtual double setAngle(double angle)=0;
};

// class MotorStepper : public Motor{
//     double current_angle=0,
//         partial=0;
//     int speed=10,
//     stepsPerRev;
//     public:
//         // return inaccuarrcy
//         double setAngle(double angle){
//             double delta = current_angle-angle+partial;
//             int moveBy = delta*stepsPerRev;
//             partial = delta-moveBy/stepsPerRev;
//             stepBy(moveBy);
//             return partial;
//         }
//     private:
//         void stepBy(int steps)
//         {
//             static_assert(false, "Not Implemented!");
//         }
// };

#include <Servo.h>

class MotorServo : public Motor {
        Servo s;
        int pin;
        double currentAngle=0,
            speed;
        public:
            Servo(int pin, double speed=100) : pin(pin), speed(speed)
            {
                s.attach(pin);
            }
            void setAngle(double angle) override
            {
                s.write(angle*180/PI);
                delay((angle-currentAngle)*1000/speed);
            }
};
