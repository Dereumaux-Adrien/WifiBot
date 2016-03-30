#include "socket.h"
#include <QTest>

Socket::Socket(QObject *parent) :
    QObject(parent)
{
    connecter=false;
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
    connecter=true;
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

void Socket::send(QByteArray trame){
    qDebug() << "sending...";
    if(connecter && socket->open(QIODevice::ReadWrite))
    {
        socket->write(trame);
        //socket->flush();
        qDebug() << "message sent";
    }
}
