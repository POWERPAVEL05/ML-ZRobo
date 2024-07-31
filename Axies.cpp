#include "Axies.hpp"

Arm::Arm(double rootLen, double extLen, Motor root, Motor ext) :
    rootLen(rootLen), extLen(extLen), ms(), root(root), ext(ext)
{
    ms.addStepper(root.stepper);
    ms.addStepper(ext.stepper);
}


void Arm::moveTo(Point p)
{
    Angles angle = pointToAngles(p); // 0-360
    Serial.println("Root: " + String(angle.root) + "°->" + String(root.getSteps(angle.root)));
    Serial.println("Ext: " + String(angle.ext) + "°->" + String(ext.getSteps(angle.root)));
    long pos[2] = {root.getSteps(angle.root), ext.getSteps(angle.ext)};
    ms.moveTo(pos);
    ms.runSpeedToPosition();
}

Angles Arm::pointToAngles(Point p)
{
    double ph2= acos(
        (p.x*p.x+p.y*p.y-rootLen*rootLen-extLen*extLen)/
            (2*rootLen*extLen));

    double phi1 = atan2(p.y,p.x)
        -atan2(extLen*sin(ph2),
                (rootLen+extLen*cos(ph2)));

    return {phi1/PI*180, ph2/PI*180};
}
