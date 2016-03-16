#include "robotcontrol.h"

RobotControl::RobotControl()
{
    leftSpeed=120;
    rightSpeed=120;
    commandFlag=80;
    zero=0;
}

/*void RobotControl::move(short speed1, short speed2, char speedFlag){
    QByteArray sbuff[9];
    sbuff[0] = 255 ;
    sbuff[1] = 0x09 ;
    sbuff[2] = (BYTE) speed1 ;
    sbuff[3] = (BYTE) (speed1 >> 8 ) ;
    sbuff[4] = (BYTE) speed2 ;
    sbuff[5] = (BYTE) (speed2 >> 8) ;
    sbuff[6] = speedFlag + 1 ;
    short mycrcsend = Crc16(sbuf+1,6);
    sbuf[7] = (BYTE)mycrcsend;
    sbuf[8] = (BYTE)(mycrcsend >> 8);
    if(WriteFile(&sbuff))
}*/

QByteArray RobotControl::move()
{
    QByteArray trame;
    trame.clear();
    trame.append((unsigned char)255);
    trame.append((unsigned char)7);
    trame.append((unsigned char)leftSpeed);
    trame.append((unsigned char)zero);
    trame.append((unsigned char)rightSpeed);
    trame.append((unsigned char)zero);
    trame.append((unsigned char)commandFlag);
    short resCrc = Crc16(trame);
    trame.append((char)resCrc);
    trame.append((char)(resCrc>>8));
    return trame;
}

short RobotControl::Crc16(QByteArray trame)
{
    unsigned char* trameChar = (unsigned char*)trame.constData(); //Cast sous forme de char*
    unsigned int crc = 0xFFFF;
    unsigned int polynome = 0xA011;
    unsigned int cptBits;
    unsigned int parity = 0;
    for(int cpt = 1; cpt < trame.length(); cpt++)
    {
        crc ^= *(trameChar + cpt);

        for(cptBits = 0; cptBits <= 7 ; cpt++)
        {
            parity = crc;
            crc >>= 1;
            if(parity%2)
                crc ^= polynome;
        }
    }

    return crc;
}
