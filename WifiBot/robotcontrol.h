#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <windows.h>
#include <QByteArray>

class RobotControl
{
public:
    RobotControl();
    QByteArray move();
    short Crc16(QByteArray trame);

private:
    char leftSpeed;
    char rightSpeed;
    char commandFlag;
    char zero;
};

#endif // ROBOTCONTROL_H
