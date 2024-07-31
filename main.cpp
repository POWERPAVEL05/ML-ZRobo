#include "DrawRobot.hpp"

#define cm

DrawRobot<Arm> robot;

void setup()
{
    Serial.begin(115200);

    Motor root(AccelStepper(8,4,6,5,7), 4076);
    Motor ext(AccelStepper(8,8,9,10,11), 4076);

    robot = {
    .axies = Arm(11 cm, 11.5 cm, root, ext),
        .gantry = Gantry(6, 7)
    };

    // robot.axies.moveTo({22.5,0});
    robot.axies.moveTo({11,11.5});

}
void loop()
{
    int cmd = Serial.parseInt();
    switch(cmd){
        case 0:{
            int x = Serial.parseInt();
            int y = Serial.parseInt();
            robot.axies.moveTo({x,y});
            break;
        }
        case 1: {
            int tool = Serial.parseInt();
            robot.gantry.setTool(tool); // ist tool
        }

    }

}
