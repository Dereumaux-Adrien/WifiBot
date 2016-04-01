#include "robotcontrol.h"
#include <QtCore>
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkAccessManager>

RobotControl::RobotControl()
{
    socket.connectSocket();
    rightSpeed = 0 ;
    leftSpeed = 0;
    commandFlag = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MySlot()));
    timer->start(25);
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

void RobotControl::MySlot(){
    move();
}

void RobotControl::setRightSpeed(char speed){
    rightSpeed = speed ;
}

void RobotControl::setLeftSpeed(char speed){
    leftSpeed = speed ;
}

void RobotControl::setCommandFlag(char flag){
    commandFlag = flag;
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

void RobotControl::moveCamera(char direction){
    /*QNetworkAccessManager nam;
    QNetworkRequest req;
    req.setUrl(QUrl("http://www.google.com"));
    nam->get(myRequest);
    /*if(direction='U'){
        QDebug("jesuisla");
        req=QNetworkRequest( QUrl( QString("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200") ) );
    }else if(direction='D'){
        //req( QUrl( QString("http://ip.jsontest.com/") ) );
    }else if(direction='R'){
        //req( QUrl( QString("http://ip.jsontest.com/") ) );
    }else if(direction='L'){
        //req( QUrl( QString("http://ip.jsontest.com/") ) );
    }*/
    //mgr.get(req);
}
