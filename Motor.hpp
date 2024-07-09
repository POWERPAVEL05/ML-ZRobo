#pragma once
#include <math.h>
#ifndef PI
#define PI 3.14159265358979
#endif
class Motor{
    public:
        // return inaccuarrcy
        virtual double setAngle(double angle)=0;
        virtual double update(int steps)=0;
};

class StepperMotor : public Motor
{
    double partial=0;
    int speed,
      stepsPerRev;
    double target=0;
    int current=0;
    public:
        StepperMotor(int stepsPerRev, int speed=5)
        : speed(speed), stepsPerRev(stepsPerRev)
        {}
        // return inaccuarrcy
        double setAngle(double angle) override
        {
            target = angle*stepsPerRev/360.0;
        }
        double update(int steps) override
        {
            double delta = target/steps+partial;
            partial = delta-(int)delta;
            current+=delta;
            stepBy(delta);
            return 0;
        }
    private:
        virtual void stepBy(int delta) =0;
};
#include "Stepper.h"
class SmallMotor : public StepperMotor {
    Stepper s;

    public:
        SmallMotor(int in1, int in2, int in3, int in4, int stepsPerRev, int speed=5)
        : s(stepsPerRev, in1, in2, in3, in4), StepperMotor(stepsPerRev, speed)
        {
            s.setSpeed(speed);
        }
    private:
        void stepBy(int delta) override
        {
            Serial.println(delta);
            s.step(delta);
        }

};

#include "AccelStepper.h"

class AccelMotor : public StepperMotor {
    AccelStepper stepper;
    public:
        AccelMotor(int stepPin, int dirPin, int stepsPerRev, int speed=1000)
        : stepper(1, stepPin, dirPin), StepperMotor(stepsPerRev, speed)
        {
            stepper.setCurrentPosition(0);
            stepper.setMaxSpeed(10000);
            stepper.setAcceleration(500);
            stepper.setSpeed(500);
        }

        // double update() override
        // {
        //     if(stepper.currentPosition() < target)
        //     {
        //         stepper.setSpeed(speed);
        //         stepper.runSpeed();
        //     }
        //     else if(stepper.currentPosition() > target)
        //     {
        //         stepper.setSpeed(-speed);
        //         stepper.runSpeed();
        //     } else {
        //         stepper.setSpeed(0);
        //         stepper.runSpeed();
        //     }
        // }
        private:
        void stepBy(int delta) override
        {
            stepper.moveTo(stepper.currentPosition()+delta);
            stepper.runToPosition();
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
        double update() {};
};
