#include "robotcontrol.h"

RobotControl::RobotControl()
{
    rightSpeed = 0 ;
    leftSpeed = 0;
    commandFlag = 0;
    batterie=0;
    cameraSpeed=100;
    IP="192.168.1.106";
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MySlot()));
    IRBL = 0 ;
    IRBR = 0 ;
    IRFL = 0 ;
    IRFR = 0 ;
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
    traitementRetour();
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
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-"+ QString::number(cameraSpeed)));
        nam->get(req);
    }else if(direction=='D'){
        QNetworkRequest req;
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value="+ QString::number(cameraSpeed)));
        nam->get(req);
    }else if(direction=='R'){
        QNetworkRequest req;
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-"+ QString::number(cameraSpeed)));
        nam->get(req);
    }else if(direction=='L'){
        QNetworkRequest req;
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value="+ QString::number(cameraSpeed)));
        nam->get(req);
    }else if(direction=='F'){
        QNetworkRequest req;
        req.setUrl(QUrl("http://"+IP+":8080/?action=command&dest=0&plugin=0&id=168062211&group=1&value=3"));
        nam->get(req);
    }
}

void RobotControl::traitementRetour(){
    QByteArray buffer=socket.getBuffer();
    if(!buffer.isEmpty()){
        batterie=((unsigned char)buffer.at(2));
        realSpeedL=((unsigned char)buffer.at(1) << 8) + (unsigned char)buffer.at(0);
        realSpeedR=((unsigned char)buffer.at(10) << 8) + (unsigned char)buffer.at(9);
        if (realSpeedL > 32767)
            realSpeedL-=65536;
        if (realSpeedR > 32767)
            realSpeedR-=65536;
        IRFL=(unsigned char)buffer.at(3);
        IRBR=(unsigned char)buffer.at(4);
        IRFR=(unsigned char)buffer.at(11);
        IRBL=(unsigned char)buffer.at(12);
    }
}

int RobotControl::getBatterie(){
    return batterie;
}

int RobotControl::getRealSpeedR(){
    return realSpeedR ;
}

int RobotControl::getRealSpeedL(){
    return realSpeedL ;
}

int RobotControl::getIRBL(){
    return IRBL ;
}

int RobotControl::getIRBR(){
    return IRBR ;
}

int RobotControl::getIRFL(){
    return IRFL ;
}

int RobotControl::getIRFR(){
    return IRFR ;
}

void RobotControl::setCameraSpeed(int cameraSpeed){
    this->cameraSpeed=cameraSpeed;
}
