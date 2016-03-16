#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include "windef.h"

class RobotControl
{
public:
    RobotControl();
    move(short speed1, short speed2, BYTE speedFlag);
};

#endif // ROBOTCONTROL_H
