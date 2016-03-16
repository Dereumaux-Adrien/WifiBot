#include "socket.h"
#include <QTest>

Socket::Socket(QObject *parent) :
    QObject(parent)
{
}

void Socket::connectSocket()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";

    socket->connectToHost("192.168.1.106", 15020);

    //En attente de connexion
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

void Socket::connected()
{
    qDebug() << "connected...";
}

void Socket::disconnected()
{
    qDebug() << "disconnected...";
}

void Socket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Socket::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}

void Socket::send(){
    qDebug() << "sending...";
    /*QByteArray trame=trameTCP();
    for(int i=0;i<100000;i++){
        QTest::qSleep(25);
        socket->write(trame);
    }*/
}
