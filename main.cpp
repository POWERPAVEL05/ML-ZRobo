#include "DrawRobot.hpp"

#define cm

void setup()
{
    Serial.begin(115200);

    Motor root(AccelStepper(8,4,6,5,7), 4076);
    Motor ext(AccelStepper(8,8,9,10,11), 4076);
    Motor dummy(AccelStepper(1,23,24), 200, 4000);

    // ext.stepper.runToNewPosition(ext.getSteps(180));
    // root.stepper.runToNewPosition(ext.getSteps(180));

    DrawRobot<Arm> robot = {
    .axies = Arm(11 cm, 11.5 cm, root, ext),
        .gantry = Gantry(6, 7)
    };

    // robot.axies.moveTo({22.5,0});
    robot.axies.moveTo({11,11.5});

    while(true)
        ;
}
void loop()
{
}
