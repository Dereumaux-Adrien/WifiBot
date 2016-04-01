#include "robotcontrol.h"
#include <QtCore>
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkAccessManager>

RobotControl::RobotControl()
{
    rightSpeed = 0 ;
    leftSpeed = 0;
    commandFlag = 0;
    IP="192.168.1.106";
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MySlot()));
}

void RobotControl::connexion(){
    socket.connectSocket();
    timer->start(25);
}

QString RobotControl::getIP(){
    return IP;
}

void RobotControl::setIP(QString s){
    IP=s;
    socket.setIP(IP);
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
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);
    if(direction=='U'){
        QNetworkRequest req;
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-100"));
        nam->get(req);
    }else if(direction=='D'){
        QNetworkRequest req;
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=100"));
        nam->get(req);
    }else if(direction=='R'){
        QNetworkRequest req;
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-100"));
        nam->get(req);
    }else if(direction=='L'){
        QNetworkRequest req;
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=100"));
        nam->get(req);
    }
}
