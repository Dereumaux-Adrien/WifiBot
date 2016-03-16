#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <windows.h>

class RobotControl
{
public:
    RobotControl();
    void move(short speed1, short speed2, BYTE speedFlag);
};

#endif // ROBOTCONTROL_H
