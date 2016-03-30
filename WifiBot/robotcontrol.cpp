#include "robotcontrol.h"

RobotControl::RobotControl()
{
    leftSpeed=120;
    rightSpeed=120;
    commandFlag=80;
    socket.connectSocket();
}

void RobotControl::move()
{
    QByteArray trame;
    trame.clear();
    trame.append((char)0xff);
    trame.append((char)0x07);
    trame.append((char)leftSpeed);
    trame.append((char)0);
    trame.append((char)rightSpeed);
    trame.append((char)0);
    trame.append((char)commandFlag);
    quint16 crc = Crc16(&trame);
    trame.append((char)crc);
    trame.append((char)(crc>>8));
    socket.send(trame);

}

quint16 RobotControl::Crc16(QByteArray* trame){
    unsigned char *data = (unsigned char* )trame->constData();
    quint16 crc = 0xFFFF;
    quint16 polynome = 0xA001;
    quint16 parity = 0;
    for(int pos=1; pos < trame->length(); pos++){
        crc ^= *(data+pos);
        for (unsigned int cpt = 0; cpt <= 7 ; cpt++){
            parity= crc;
            crc >>= 1;
            if (parity%2 == true) crc ^= polynome;
        }
    }
    return crc;
}
