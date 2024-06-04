#pragma once
#include <math.h>
#ifndef PI
#define PI 3.14159265358979
#endif
class Motor{
    public:
        // return inaccuarrcy
        virtual double setAngle(double angle)=0;
        virtual double update()=0;
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
        uint8_t pin;
        double currentAngle=0,
            speed;
        public:
            MotorServo(uint8_t pin, double speed=100) : pin(pin), speed(speed)
            {
                s.attach(pin);
            }
            double setAngle(double angle) override
            {
              Serial.println(angle);
                for(int i = currentAngle; i < angle; i++){
                  s.write(i);
                  delay(1000/speed);
                }
                currentAngle=angle;
                return 0;
            }
        double update() override {};
};
