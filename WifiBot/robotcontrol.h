#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <windows.h>
#include <QByteArray>
#include "socket.h"

class RobotControl
{
public:
    RobotControl();
    void move();
    quint16 Crc16(QByteArray* trame);

private:
    Socket socket;
    char leftSpeed;
    char rightSpeed;
    char commandFlag;
};

#endif // ROBOTCONTROL_H
