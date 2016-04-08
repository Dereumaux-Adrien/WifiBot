#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <windows.h>
#include <QByteArray>
#include <QtCore>
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkAccessManager>
#include "socket.h"

class RobotControl : public QObject
{

    Q_OBJECT

public:
    RobotControl();
    void move();
    quint16 Crc16(QByteArray* trame);
    void setRightSpeed(char speed);
    void setLeftSpeed(char speed);
    void setCommandFlag(char flag);
    void moveCamera(char direction);
    QString getIP();
    void setIP(QString s);
    void connexion();
    void traitementRetour();
    int getBatterie();
    int getRealSpeedR();
    int getRealSpeedL();
    int getIRFR() ;
    int getIRFL() ;
    int getIRBR() ;
    int getIRBL() ;
    void setCameraSpeed(int cameraSpeed);

public slots:
    void MySlot();

private:
    Socket socket;
    QTimer *timer ;
    char rightSpeed ;
    char leftSpeed ;
    char commandFlag ;
    int cameraSpeed;
    QString IP;
    int batterie;
    int realSpeedL;
    int realSpeedR;
    int IRFR ;
    int IRFL ;
    int IRBR ;
    int IRBL ;
};

#endif // ROBOTCONTROL_H
