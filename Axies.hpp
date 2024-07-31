#pragma once
#include "AccelStepper.h"
#include "MultiStepper.h"

#ifndef PI
#define PI 3.14159265358979
#endif

struct Point {double x,y;};
struct Angles {double root, ext;};

class Axies
{
    public:
        virtual void moveTo(Point p)=0;
};

struct Motor
{
    AccelStepper stepper;
    int stepsPerRev=-1;
    Motor(AccelStepper stepper, int stepsPerRev, int speed=4000):
        stepper(stepper), stepsPerRev(stepsPerRev)
    {
        this->stepper.setAcceleration(1000);
        this->stepper.setMaxSpeed(speed);
        this->stepper.setSpeed(speed);
    }

    long getSteps(double deg)
    {
        return deg/360.0*stepsPerRev;
    }
};

class Arm
{
    double rootLen, extLen;
    Motor root, ext;
    MultiStepper ms;
    public:
        Arm(double rootLen, double extLen, Motor root, Motor ext);
        void moveTo(Point p);
    private:
        //calculates the angles of the two sections so the end of the second is at point p
        Angles pointToAngles(Point p);
};
