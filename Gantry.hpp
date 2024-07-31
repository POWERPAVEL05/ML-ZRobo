#pragma once
#include <Servo.h>

class Gantry
{
    Servo use, // servo for lowering tool
        select;// Servo to switch between tools
               // ^ currently unused

    public:
        Gantry(int usePin, int selectPin)
        {
            use.attach(usePin);
            select.attach(selectPin);
        }
        enum Tool {
            NONE,
            PEN
        };
        void setTool(Tool tool);

};
