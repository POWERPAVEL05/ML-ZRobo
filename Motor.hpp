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

#include "Stepper.h"
class MotorStepper : public Motor {
    Stepper s;
    double current_angle=0,
        partial=0;
    int speed,
    stepsPerRev;
    public:
        MotorStepper(int in1, int in2, int in3, int in4, int stepsPerRev, int speed=5)
        : s(stepsPerRev, in1, in2, in3, in4), speed(speed), stepsPerRev(stepsPerRev)
        {
            s.setSpeed(speed);
        }
        // return inaccuarrcy
        double setAngle(double angle){
            double delta = angle-current_angle+partial;
            int moveBy = delta*stepsPerRev/360;
            partial = delta-(moveBy*360)/stepsPerRev;
            stepBy(moveBy);
            current_angle+=moveBy;
            return partial;
        }
        double update()
        {}
    private:
        void stepBy(int steps)
        {
            s.step(steps);
        }
};

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
                double dAngle = angle - currentAngle;
              Serial.println(dAngle);
                s.write(angle);
                delay(1000/speed*dAngle);
                currentAngle=angle;
                return 0;
            }
        double update() override {};
};
