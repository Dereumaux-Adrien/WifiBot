#include "socket.h"

Socket::Socket(QObject *parent) :
    QObject(parent)
{
    connecter=false;
    IP="192.168.1.106";
}

void Socket::setIP(QString s){
    IP=s;
}

void Socket::connectSocket()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";

    socket->connectToHost(IP, 15020);

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
    //qDebug() << bytes << " bytes written...";
}

void Socket::readyRead()
{
    // read the data from the socket
    buffer.clear();
    buffer.append(socket->read(21), 21);
    socket->readAll();
}

void Socket::send(QByteArray trame){
    if(connecter && socket->open(QIODevice::ReadWrite))
    {
        socket->write(trame);
        //socket->flush();
    }
}

QByteArray Socket::getBuffer(){
    return buffer;
}
